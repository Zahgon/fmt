// Formatting library for C++ - optional OS-specific functionality
//
// Copyright (c) 2012 - present, Victor Zverovich and {fmt} contributors
// All rights reserved.
//
// For the license information refer to format.h.

// Disable bogus MSVC warnings.
#if !defined(_CRT_SECURE_NO_WARNINGS) && defined(_MSC_VER)
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include "fmt/os.h"

#ifndef FMT_MODULE

#  if FMT_USE_FCNTL
#    include <sys/stat.h>
#    include <sys/types.h>

#    ifdef _WRS_KERNEL    // VxWorks7 kernel
#      include <ioLib.h>  // getpagesize
#    endif

#    ifndef _WIN32
#      include <unistd.h>
#    else
#      ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#      endif
#      include <io.h>
#    endif  // _WIN32
#  endif    // FMT_USE_FCNTL

#  ifdef _WIN32
#    include <windows.h>

#    include <climits>  // CHAR_BIT
#  endif
#endif

#ifdef _WIN32
#  ifndef S_IRUSR
#    define S_IRUSR _S_IREAD
#  endif
#  ifndef S_IWUSR
#    define S_IWUSR _S_IWRITE
#  endif
#  ifndef S_IRGRP
#    define S_IRGRP 0
#  endif
#  ifndef S_IWGRP
#    define S_IWGRP 0
#  endif
#  ifndef S_IROTH
#    define S_IROTH 0
#  endif
#  ifndef S_IWOTH
#    define S_IWOTH 0
#  endif
#endif

namespace {
#ifdef _WIN32

// Return type of read and write functions.
using rwresult = int;

// On Windows the count argument to read and write is unsigned, so convert
// it from size_t preventing integer overflow.
inline unsigned convert_rwcount(size_t count) { __builtin_trap() /* STUB: not implemented */; }

class system_message {
  system_message(const system_message&) = delete;
  void operator=(const system_message&) = delete;

  unsigned long result_;
  wchar_t* message_;

  static bool is_whitespace(wchar_t c) noexcept { __builtin_trap() /* STUB: not implemented */; }

 public:
  explicit system_message(unsigned long error_code)
      : result_(0), message_(nullptr) { __builtin_trap() /* STUB: not implemented */; }
  ~system_message() { __builtin_trap() /* STUB: not implemented */; }
  explicit operator bool() const noexcept { __builtin_trap() /* STUB: not implemented */; }
  operator fmt::basic_string_view<wchar_t>() const noexcept { __builtin_trap() /* STUB: not implemented */; }
};

class utf8_system_category final : public std::error_category {
 public:
  const char* name() const noexcept override { __builtin_trap() /* STUB: not implemented */; }
  std::string message(int error_code) const override { __builtin_trap() /* STUB: not implemented */; }
};

#elif FMT_USE_FCNTL

// Return type of read and write functions.
using rwresult = ssize_t;

inline auto convert_rwcount(size_t count) -> size_t { __builtin_trap() /* STUB: not implemented */; }

#endif
}  // namespace

FMT_BEGIN_NAMESPACE

#ifdef _WIN32

FMT_API const std::error_category& system_category() noexcept { __builtin_trap() /* STUB: not implemented */; }

std::system_error vwindows_error(int err_code, string_view format_str,
                                 format_args args) { __builtin_trap() /* STUB: not implemented */; }

void detail::format_windows_error(detail::buffer<char>& out, int error_code,
                                  const char* message) noexcept { __builtin_trap() /* STUB: not implemented */; }

void report_windows_error(int error_code, const char* message) noexcept { __builtin_trap() /* STUB: not implemented */; }

#endif  // _WIN32

buffered_file::~buffered_file() noexcept { __builtin_trap() /* STUB: not implemented */; }

buffered_file::buffered_file(cstring_view filename, cstring_view mode) { __builtin_trap() /* STUB: not implemented */; }

void buffered_file::close() { __builtin_trap() /* STUB: not implemented */; }

auto buffered_file::descriptor() const -> int { __builtin_trap() /* STUB: not implemented */; }

#if FMT_USE_FCNTL
#  ifdef _WIN32
using mode_t = int;
#  endif

constexpr mode_t default_open_mode =
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

file::file(cstring_view path, int oflag) { __builtin_trap() /* STUB: not implemented */; }

file::~file() noexcept { __builtin_trap() /* STUB: not implemented */; }

void file::close() { __builtin_trap() /* STUB: not implemented */; }

auto file::size() const -> long long { __builtin_trap() /* STUB: not implemented */; }

auto file::read(void* buffer, size_t count) -> size_t { __builtin_trap() /* STUB: not implemented */; }

auto file::write(const void* buffer, size_t count) -> size_t { __builtin_trap() /* STUB: not implemented */; }

auto file::dup(int fd) -> file { __builtin_trap() /* STUB: not implemented */; }

void file::dup2(int fd) { __builtin_trap() /* STUB: not implemented */; }

void file::dup2(int fd, std::error_code& ec) noexcept { __builtin_trap() /* STUB: not implemented */; }

auto file::fdopen(const char* mode) -> buffered_file { __builtin_trap() /* STUB: not implemented */; }

#  if defined(_WIN32) && !defined(__MINGW32__)
file file::open_windows_file(wcstring_view path, int oflag) { __builtin_trap() /* STUB: not implemented */; }
#  endif

pipe::pipe() { __builtin_trap() /* STUB: not implemented */; }

#  if !defined(__MSDOS__)
auto getpagesize() -> long { __builtin_trap() /* STUB: not implemented */; }
#  endif

void ostream::grow(buffer<char>& buf, size_t) { __builtin_trap() /* STUB: not implemented */; }

ostream::ostream(cstring_view path, const detail::ostream_params& params)
    : buffer<char>(grow), file_(path, params.oflag) { __builtin_trap() /* STUB: not implemented */; }

ostream::ostream(ostream&& other) noexcept
    : buffer<char>(grow, other.data(), other.size(), other.capacity()),
      file_(std::move(other.file_)) { __builtin_trap() /* STUB: not implemented */; }

ostream::~ostream() { __builtin_trap() /* STUB: not implemented */; }
#endif  // FMT_USE_FCNTL
FMT_END_NAMESPACE
