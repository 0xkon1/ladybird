/*
 * Copyright (c) 2020-2023, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2021-2022, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2023, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/MainThreadVM.h>
#include <LibWeb/HTML/TraversableNavigable.h>
#include <WebContent/ConnectionFromClient.h>
#include <WebContent/PageClient.h>
#include <WebContent/PageHost.h>
#include <WebContent/WebDriverConnection.h>

namespace WebContent {

PageHost::PageHost(ConnectionFromClient& client)
    : m_client(client)
{
    auto& first_page = create_page();
    Web::HTML::TraversableNavigable::create_a_fresh_top_level_traversable(first_page.page(), URL::about_blank());
}

PageClient& PageHost::create_page()
{
    m_pages.set(m_next_id, PageClient::create(Web::Bindings::main_thread_vm(), *this, m_next_id));
    auto& page_client = *m_pages.get(m_next_id).value();
    page_client.page().set_is_cookies_enabled(PageClient::initial_cookies_enabled());
    ++m_next_id;
    return page_client;
}

void PageHost::remove_page(Badge<PageClient>, u64 index)
{
    m_pages.remove(index);
}

Optional<PageClient&> PageHost::page(u64 index)
{
    return m_pages.get(index).map([](auto& value) -> PageClient& {
        return *value;
    });
}

PageHost::~PageHost() = default;

}
