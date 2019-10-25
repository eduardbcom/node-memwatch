/*
 * 2012|lloyd|do what the fuck you want to
 */

#include <v8.h>
#include <node.h>

#include "heapdiff.hh"
#include "memwatch.hh"

using namespace v8;

extern "C" {
    void init(Local<Object> exports)
    {
        Isolate * isolate = exports->GetIsolate();

        Nan::HandleScope scope;

        heapdiff::HeapDiff::Initialize(exports);
        
        Nan::SetMethod(exports, "upon_gc", memwatch::upon_gc);
        Nan::SetMethod(exports, "gc", memwatch::trigger_gc);

        isolate->AddGCEpilogueCallback(memwatch::after_gc);
    }

    NODE_MODULE(memwatch, init);
};
