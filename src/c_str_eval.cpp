#include <iostream>
#include <string>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <iterator>
#include <regex>
#include "exprtk.hpp"

std::string hex_to_dec(std::string hex_str) {
  // Use std::stoi with base 16 to convert the hex string to an integer
  uint64_t dec_num = std::stoull(hex_str, nullptr, 16);
  // Use std::to_string to convert the integer to a decimal string
  std::string dec_str = std::to_string(dec_num);
  // Return the decimal string
  return dec_str;
}

std::string hex_to_dec_whole(std::string const & hex_str)
{
  std::regex re("0[xX][0-9a-fA-F]+");
  std::string in_str(hex_str);
  std::string out;
  std::string::const_iterator it = in_str.cbegin(), end = in_str.cend();
  for (std::smatch match; std::regex_search(it, end, match, re); it = match[0].second)
  {
    out += match.prefix();
    // std::cout << match.str() << std::endl;
    out += hex_to_dec(match.str()); // replace here
  }
  out.append(it, end);
  return out;
}

std::string find_n_replace(std::string const & in, std::string const & from, std::string const & to )
{
  return std::regex_replace(in, std::regex(from), to);
}

// A function that takes a c style string as input and evaluates it using exprtk
extern "C" int64_t eval_c_string(const char* input) {
  std::string target = hex_to_dec_whole(input);
  target = find_n_replace(target, "&&", "&");
  target = find_n_replace(target, "\\|\\|", "|");

  // Define the symbol table, expression and parser
  typedef exprtk::symbol_table<double> symbol_table_t;
  typedef exprtk::expression<double> expression_t;
  typedef exprtk::parser<double> parser_t;

  // Create a symbol table and add some constants
  symbol_table_t symbol_table;
  symbol_table.add_constants();

  // Create an expression and register the symbol table
  expression_t expression;
  expression.register_symbol_table(symbol_table);

  // Create a parser and compile the input string
  parser_t parser;
  if (!parser.compile(target, expression)) {
    // If the compilation fails, print the error and return NaN
    std::cerr << "Error: " << parser.error() << std::endl;
    assert(0);
  }

  // Evaluate and return the expression value
  return std::round(expression.value());
}
