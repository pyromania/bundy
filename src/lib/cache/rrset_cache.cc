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

#include <config.h>

#include <string>
#include "rrset_cache.h"
#include <nsas/nsas_entry_compare.h>
#include <nsas/hash_table.h>
#include <nsas/hash_deleter.h>

using namespace isc::nsas;
using namespace isc::dns;
using namespace std;

namespace isc {
namespace cache {

RRsetCache::RRsetCache(uint32_t cache_size,
                       uint16_t rrset_class):
    class_(rrset_class),
    rrset_table_(new NsasEntryCompare<RRsetEntry>, cache_size),
    rrset_lru_((3 * cache_size),
                  new HashDeleter<RRsetEntry>(rrset_table_))
{
}

RRsetEntryPtr
RRsetCache::lookup(const isc::dns::Name& qname,
                   const isc::dns::RRType& qtype)
{
    const string entry_name = genCacheEntryName(qname, qtype);
    RRsetEntryPtr entry_ptr = rrset_table_.get(HashKey(entry_name, RRClass(class_)));
    if (entry_ptr) {
        if (entry_ptr->getExpireTime() > time(NULL)) {
            // Only touch the non-expired rrset entries
            rrset_lru_.touch(entry_ptr);
            return (entry_ptr);
        } else {
            // the rrset entry has expired, so just remove it from
            // hash table and lru list.
            rrset_table_.remove(entry_ptr->hashKey());
            rrset_lru_.remove(entry_ptr);
        }
    }

    return (RRsetEntryPtr());
}

RRsetEntryPtr
RRsetCache::update(const isc::dns::RRset& rrset, const RRsetTrustLevel& level) {
    // TODO: If the RRset is an NS, we should update the NSAS as well
    // lookup first
    RRsetEntryPtr entry_ptr = lookup(rrset.getName(), rrset.getType());
    if (entry_ptr) {
        if (entry_ptr->getTrustLevel() > level) {
            // existed rrset entry is more authoritative, just return it
            return (entry_ptr);
        } else {
            // Remove the old rrset entry from the lru list.
            rrset_lru_.remove(entry_ptr);
        }
    }

    entry_ptr.reset(new RRsetEntry(rrset, level));
    rrset_table_.add(entry_ptr, entry_ptr->hashKey(), true);
    rrset_lru_.add(entry_ptr);
    return (entry_ptr);
}

#if 0
void
RRsetCache::dump(const std::string&) {
    //TODO
}

void
RRsetCache::load(const std::string&) {
    //TODO
}

bool
RRsetCache::resize(uint32_t) {
    //TODO
    return (true);
}
#endif

} // namespace cache
} // namespace isc
