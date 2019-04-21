//
// Created by sztergbaum roman on 2019-04-21.
//

#pragma once

#ifdef _MSC_VER // Visual Studio
#define pretty_function __FUNCSIG__
#else
#define pretty_function __PRETTY_FUNCTION__ // NOLINT(cppcoreguidelines-macro-usage)
#endif

