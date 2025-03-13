#include "HtmlDecode.h"

#include <sstream>
#include <stdexcept>
#include <unordered_map>

const char SEQUENCE_START = '&';
const char SEQUENCE_END = ';';

std::string MakeSequence(std::string code)
{
	return SEQUENCE_START + code + SEQUENCE_END;
}

const std::unordered_map<std::string, char> ENCODINGS = {
	{ MakeSequence("quot"), '"' },
	{ MakeSequence("apos"), '\'' },
	{ MakeSequence("lt"), '<' },
	{ MakeSequence("gt"), '>' },
	{ MakeSequence("amp"), '&' },
};

enum class State
{
	OUT_HTML,
	IN_HTML,
};

char GetDecodedChar(std::string& htmlToken)
{
	auto it = ENCODINGS.find(htmlToken);
	if (it == ENCODINGS.end())
	{
		throw std::runtime_error("Invalid html encoded sequence: '" + htmlToken + "'");
	}

	return it->second;
}

void ChangeState(State to, State& curr, std::string& htmlToken)
{
	curr = to;
	htmlToken.push_back(to == State::OUT_HTML ? SEQUENCE_END : SEQUENCE_START);
}

void ProcessSequence(std::string& htmlToken, std::string& result)
{
	char decoded = GetDecodedChar(htmlToken);
	result.push_back(decoded);

	htmlToken.clear();
}

std::string HtmlDecode(const std::string& html)
{
	std::string result;
	std::string htmlToken;
	std::istringstream iss(html);

	State state = State::OUT_HTML;

	char ch;
	while (iss.get(ch))
	{
		if (ch == SEQUENCE_START && state == State::OUT_HTML)
		{
			ChangeState(State::IN_HTML, state, htmlToken);
			continue;
		}

		if (ch == SEQUENCE_END && state == State::IN_HTML)
		{
			ChangeState(State::OUT_HTML, state, htmlToken);

			ProcessSequence(htmlToken, result);
			continue;
		}

		if (state == State::IN_HTML)
		{
			htmlToken.push_back(ch);
		}
		else
		{
			result.push_back(ch);
		}
	}

	if (state == State::IN_HTML)
	{
		result.append(htmlToken);
	}

	return result;
}
