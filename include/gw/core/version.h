#ifndef GW_CORE_VERSION_H
#define GW_CORE_VERSION_H


namespace gw::core {
    // Version information
    constexpr int VERSION_MAJOR = 0;
    constexpr int VERSION_MINOR = 1;
    constexpr int VERSION_PATCH = 0;

    // Get version as string
    const char *get_version_string();
} // namespace gw::core


#endif  // GW_CORE_VERSION_H
