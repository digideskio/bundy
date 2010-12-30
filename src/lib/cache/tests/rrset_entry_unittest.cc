// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$
#include <config.h>
#include <string>
#include <gtest/gtest.h>
#include "../cache_entry_key.h"

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {
class GenCacheKeyTest: public testing::Test {
};

TEST_F(GenCacheKeyTest, genCacheEntryKey1) {
    string name = "example.com.";
    uint16_t type = 12;
    string name_type = "example.com.12";

    pair<const char*, const int32_t> key =  genCacheEntryKey(name, type);
    EXPECT_EQ(name_type, string(key.first));
    EXPECT_EQ(name_type.length(), key.second);
}

TEST_F(GenCacheKeyTest, genCacheEntryKey2) {
    Name name("example.com");
    RRType type(1234);
    string keystr = "example.com.1234";
    pair<const char*, const int32_t> key = genCacheEntryKey(name, type);
    EXPECT_EQ(keystr, string(key.first));
    EXPECT_EQ(keystr.length(), key.second);
}

}   // namespace

