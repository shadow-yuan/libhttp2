#include "src/init.h"
#include "src/hpack/static_metadata.h"

#include "http2/http2.h"

namespace http2 {
namespace {
InitService *global_init_service = nullptr;
}  // namespace

class InitServiceImpl : public InitService {
public:
    void init() override {
        LibHttp2Initialize();
    }
    void shutdown() override {
        LibHttp2Cleanup();
    }
};

class LibraryInitializer final {
public:
    LibraryInitializer() {
        if (global_init_service == nullptr) {
            global_init_service = new InitServiceImpl;
            global_init_service->init();
        }
    }

    ~LibraryInitializer() {
        if (global_init_service) {
            global_init_service->shutdown();
            delete global_init_service;
        }
    }

    int temp() {
        return 42;
    }
};

static LibraryInitializer global_initializer;
}  // namespace http2

void LibHttp2Initialize() {
    // TODO(SHADOW):
    init_static_metadata_context();
}

void LibHttp2Cleanup() {
    // TODO(SHADOW):
    destroy_static_metadata_context();
}
