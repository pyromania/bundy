// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef ISC_RESOLVE_H
#define ISC_RESOLVE_H 1

/// This file includes all other libresolve headers, and provides
/// several helper functions used in resolving.

#include <resolve/resolver_interface.h>
#include <resolve/resolver_callback.h>
#include <resolve/response_classifier.h>

#include <dns/rcode.h>

namespace bundy {
namespace resolve {

/// \brief Create an error response
///
/// Clears the answer, authority, and additional section of the
/// given MessagePtr and sets the given error code
///
/// Notes: Assuming you have already done initial preparations
/// on the given answer message (copy the opcode, qid and question
/// section), you can simply use this to create an error response.
///
/// \param answer_message The message to clear and place the error in
/// \param error_code The error Rcode
void makeErrorMessage(bundy::dns::MessagePtr answer_message,
                      const bundy::dns::Rcode& error_code);


/// \brief Initialize a response message
///
/// Based on the given query message, this fills in the very
/// first details of the response (i.e. the Question section and
/// the Opcode). This allows for direct usage of makeErrorMessage(),
/// as well as ResolveCache.lookup().
///
/// Raises an bundy::dns::InvalidMessageOperation if reponse_message is
/// not in RENDER mode.
///
/// \param query_message The query message to take the Question, Qid,
///                      and Opcode from.
/// \param response_message The fresh response message to initialize
///                         (must be in RENDER mode)
void initResponseMessage(const bundy::dns::Message& query_message,
                         bundy::dns::Message& response_message);


/// \brief Initialize a response message
///
/// Based on the given question, this fills in the very
/// first details of the response (i.e. the Question section and the
/// Opcode Query). This allows for direct usage of makeErrorMessage(),
/// as well as ResolveCache.lookup().
///
/// Raises an bundy::dns::InvalidMessageOperation if reponse_message is
/// not in RENDER mode.
///
/// \param question The question to place in the Question section
/// \param response_message The fresh response message to initialize
///                         (must be in RENDER mode)
void initResponseMessage(const bundy::dns::Question& question,
                         bundy::dns::Message& response_message);


/// \brief Copies the parts relevant for a DNS response to the
/// target message
///
/// This adds all the RRsets in the answer, authority and
/// additional sections to the target, as well as the response
/// code
/// \param source The Message to copy the data from
/// \param target The Message to copy the data to
void copyResponseMessage(const bundy::dns::Message& source,
                         bundy::dns::MessagePtr target);


} // namespace resolve
} // namespace bundy

#endif // ISC_RESOLVE_H_
