// Don't worry about Intellisense errors here, as this file is only used in conjunction with Options.h/Options.cpp
// To add a new option, add a new variable entry and a corresponding OptionInfo in Options.cpp

// OXCE hidden, accessible only via options.cfg
/**
 * Verification level of mod data.
 * Same levels supported as `SeverityLevel`.
 */

OPT std::vector< std::pair<std::string, bool> > mods; // ordered list of available mods (lowest priority to highest) and whether they are active
