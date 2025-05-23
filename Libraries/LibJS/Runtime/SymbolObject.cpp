/*
 * Copyright (c) 2020, Matthew Olsson <mattco@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Runtime/GlobalObject.h>
#include <LibJS/Runtime/Symbol.h>
#include <LibJS/Runtime/SymbolObject.h>

namespace JS {

GC_DEFINE_ALLOCATOR(SymbolObject);

GC::Ref<SymbolObject> SymbolObject::create(Realm& realm, Symbol& primitive_symbol)
{
    return realm.create<SymbolObject>(primitive_symbol, realm.intrinsics().symbol_prototype());
}

SymbolObject::SymbolObject(Symbol& symbol, Object& prototype)
    : Object(ConstructWithPrototypeTag::Tag, prototype)
    , m_symbol(symbol)
{
}

void SymbolObject::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_symbol);
}

}
