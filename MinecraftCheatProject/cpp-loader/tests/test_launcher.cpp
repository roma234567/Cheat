#include <cassert>

#include "../src/AuthManager.h"

int main() {
    AuthManager auth;
    const auto uuid = auth.generateOfflineUUID("TestUser");

    assert(uuid.size() == 36);
    assert(uuid[8] == '-');
    assert(uuid[13] == '-');
    assert(uuid[18] == '-');
    assert(uuid[23] == '-');

    // TODO: Add integration tests for full launch argument assembly.
    return 0;
}
