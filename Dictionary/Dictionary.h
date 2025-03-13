#pragma once

#include <istream>
#include <map>
#include <ostream>
#include <set>
#include <string>

namespace dictionary
{
using DictionaryType = std::map<std::string, std::set<std::string>>;
using Entry = std::pair<std::string, std::string>;

/**
 *	\brief Input line format: <word> -- <translation>
 */
DictionaryType CreateFromStream(std::istream& input);

/**
 *	\brief Output line format: <word> -- <translation>
 */
void WriteToStream(std::ostream& output, const DictionaryType& dictionary);

void AddToDictionary(DictionaryType& dictionary, const Entry& entry);

std::set<std::string> FindTranslations(const DictionaryType& dictionary, const std::string& word);

void PrintTranslations(std::ostream& output, const std::set<std::string>& translations);
} // namespace dictionary
