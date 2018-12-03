# yal (Yet Another Logging Library)

Another Logging Library implemented in C++ (17 is required)

## Motivation

I wanted to have a multipurpose Logging Library without having to implement it for every Project on my own. I looked at spdlog but i didn't want to restrict myself to a certain license and be able to choose it on my own. And i have no clue about laws and this type of stuff. Since i like to use different Languages and OS's (?) i wanted to make one i can use in Java / C# etc.

## Naming and Definition
###Sink
Part where the log messages get written to a Webservice/Console/File or whatever you prefer. It gets called by the logging thread.
###Logger
Interface to get a stream on a certain logging level.
###Logger Stream
Stream Object, can be written to by <<, print(ln). It will emit a new Log message if it encounters a new '\n' character.
###Logger Manager
Owns Sinks and creates a stream, which is able to write to it.

## Design Decisions
I have an interface for almost every string type with a different encoding. 
The Problem is the output encoding is defined by the sink. Currently it's just a pass down to the sink due to maybe having different ways to convert the encoding to the needed one. 
For Example:
Input from the Interface is std::wstring which is UTF16 in Windows. But what to do if you want to write it to a UTF-8 File.
Currently you don't have any conversion implemented or supported.
I didnt want to depend on any 3rd person library for encoding/decoding. Also codecvt can be troublesome due to deprecation.
Another "side" problem got solved by this decision:
I didn't want to encode everything first in UTF-8 and then pass it down since this would put work on the thread who wants to log and its maybe in its critical section where performance matters. I didn't want to make a user decide to log or not log because you have a small delay due to conversion, so everything is done down inside the sink. Also it would lead to situations like passing and ANSI string and converting it to UTF-8 and trying to log it onto std::cout, which would require a conversion to UTF16/32 due ANSI is the extension of ASCII. Worse if its an ASCII string.

## Sinks 
You have to implement them by yourself due to limitations of usage of codecvt and 3rd Party Librarys. For how to implement them look at Examples.

## Example Usage
Short:
```
yalog::yal_manager manager{};
manager.manager.add_new_logger("cout", yalog::sinks::console_out{}, yalog::log_level::DEBUG);
manager.set_default("cout");
manager().debug() << "Hello\n";
manager("cout").debug() << "World\n";
```

Long:

Look into examples/ its way better commented then i can do here.

## String Representations

ANSI/ASCII/UTF-8 Strings are represented in std::string/std::string_view
UTF16 is either std::wstring or std::u16string
UTF32 can be std::wstring or std::u32string

## Windows / Linux and std::wstring

I don't have enough experience with Linux. As far as i know Linux uses UTF-8 for most of its APIs. Currently i defined std::wstring as UTF-32 encoded string if _WIN32/_WIN64 isn't defined but this has to be revisited.

## TODOs

- Check if a lock free queue gives a lock free queue gives any perfomance gain over my condition variable / mutex usage. (Probabbly)
- Making formatting configurable or at least some what standarized.
- Write a gui to parse Logs & filter them
- With C++20 use std::u8string instead of std::string
- Expose a C API