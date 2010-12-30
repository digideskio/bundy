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

#ifndef __MESSAGE_ENTRY_H
#define __MESSAGE_ENTRY_H

#include <vector>
#include <dns/message.h>
#include <nsas/nsas_entry.h>
#include <nsas/fetchable.h>


using namespace isc::nsas;

namespace isc {
namespace cache {

class RRsetEntry;
class RRsetCache;

/// \brief Message Entry
/// The object of MessageEntry represents one response message
/// answered to the recursor client. 
class MessageEntry : public NsasEntry<MessageEntry>, 
                     public Fetchable 
{
public:

    /// \brief Initialize the message entry object with one dns 
    /// message.
    /// \param message The message used to initialize MessageEntry.
    /// \param rrset_cache the pointer of RRsetCache. When one message
    /// entry is created, some new rrset entries may be created/updated
    /// if they doesn't exist in the rrset cache.
    MessageEntry(const isc::dns::Message& message,
                 boost::shared_ptr<RRsetCache> rrset_cache);

    /// \brief generate one dns message according 
    /// the rrsets information of the message.
    /// \param response generated dns message.
    /// \param time_now set the ttl of each rrset in the message
    ///        as "expire_time - time_now" (expire_time is the 
    ///        expiration time of the rrset).
    /// \param query_header the query message header.
    /// \return return true if the response message can be generated 
    /// from the cached information, or else, return false.
    bool genMessage(const time_t& time_now,
                    const uint16_t query_header,
                    isc::dns::Message& response);
protected:
    // Initialize the message entry with dns message.
    void initMessageEntry(const isc::dns::Message& message);

private:
    time_t expire_time_;  // Expiration time of the message.

    std::string query_name_; // query name of the message.
    uint16_t query_class_; // query class of the message.
    uint16_t query_type_; // query type of message.

    uint16_t query_header; // query header of the message.
    uint16_t query_count_; // query count in query section.
    uint16_t answer_count_; // rrset count in answer section.
    uint16_t authority_count_; // rrset count in authority section.
    uint16_t additional_count_; // rrset count in addition section.

    std::vector<boost::shared_ptr<RRsetEntry*> > rrsets_;
    boost::shared_ptr<RRsetCache> rrset_cache_;
};
    
typedef boost::shared_ptr<MessageEntry> MessageEntryPtr;

} // namespace cache
} // namespace isc

#endif // __MESSAGE_ENTRY_H

