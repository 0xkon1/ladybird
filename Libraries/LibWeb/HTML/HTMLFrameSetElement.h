/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/HTML/HTMLElement.h>
#include <LibWeb/HTML/WindowEventHandlers.h>

namespace Web::HTML {

// NOTE: This element is marked as obsolete, but is still listed as required by the specification.
class HTMLFrameSetElement final
    : public HTMLElement
    , public WindowEventHandlers {
    WEB_PLATFORM_OBJECT(HTMLFrameSetElement, HTMLElement);
    GC_DECLARE_ALLOCATOR(HTMLFrameSetElement);

public:
    virtual ~HTMLFrameSetElement() override;

private:
    HTMLFrameSetElement(DOM::Document&, DOM::QualifiedName);

    virtual bool is_html_frameset_element() const override { return true; }

    virtual void adjust_computed_style(CSS::ComputedProperties&) override;

    virtual void initialize(JS::Realm&) override;
    virtual void attribute_changed(FlyString const& name, Optional<String> const& old_value, Optional<String> const& value, Optional<FlyString> const& namespace_) override;

    // ^HTML::GlobalEventHandlers
    virtual GC::Ptr<EventTarget> global_event_handlers_to_event_target(FlyString const& event_name) override;

    // ^HTML::WindowEventHandlers
    virtual GC::Ptr<EventTarget> window_event_handlers_to_event_target() override;
};

}

namespace Web::DOM {

template<>
inline bool Node::fast_is<HTML::HTMLFrameSetElement>() const { return is_html_frameset_element(); }

}
