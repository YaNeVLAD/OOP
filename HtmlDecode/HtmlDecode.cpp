#include "HtmlDecode.h"

#include <sstream>
#include <stdexcept>
#include <unordered_map>

const char SEQUENCE_START = '&';
const char SEQUENCE_END = ';';

static std::string MakeSequence(std::string code)
{
	return SEQUENCE_START + code + SEQUENCE_END;
}

static std::unordered_map<std::string, char> ENCODINGS = {
	{ MakeSequence("quot"), '"' },
	{ MakeSequence("apos"), '\'' },
	{ MakeSequence("lt"), '<' },
	{ MakeSequence("gt"), '>' },
	{ MakeSequence("amp"), '&' },
};

enum class State
{
	NON_HTML,
	HTML_PROCESS,
};

static char GetDecodedChar(std::string& htmlToken)
{
	auto it = ENCODINGS.find(htmlToken);
	if (it == ENCODINGS.end())
	{
		throw std::runtime_error("Invalid html encoded sequence: '" + htmlToken + "'");
	}

	htmlToken = "";

	return it->second;
}

static void ChangeState(State to, State& curr, std::string& htmlToken)
{
	curr = to;
	htmlToken.push_back(to == State::NON_HTML ? SEQUENCE_END : SEQUENCE_START);
}

/**
 *  @throws std::runtime_error - if given wrong html encoded sequence
 */
std::string HtmlDecode(const std::string& html)
{
	std::string result;
	std::string htmlToken;
	std::istringstream iss(html);

	State state = State::NON_HTML;

	char ch;
	while (iss.get(ch))
	{
		if (ch == SEQUENCE_START && state == State::NON_HTML)
		{
			ChangeState(State::HTML_PROCESS, state, htmlToken);
			continue;
		}

		if (ch == SEQUENCE_END && state == State::HTML_PROCESS)
		{
			ChangeState(State::NON_HTML, state, htmlToken);

			char decoded = GetDecodedChar(htmlToken);
			result.push_back(decoded);

			htmlToken.clear();
			continue;
		}

		if (state == State::HTML_PROCESS)
		{
			htmlToken.push_back(ch);
		}
		else
		{
			result.push_back(ch);
		}
	}

	if (state == State::HTML_PROCESS)
	{
		result.append(htmlToken);
	}

	return result;
}
