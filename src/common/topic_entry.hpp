#pragma once

#include <string>
#include <vector>

struct topic_entry {
    std::string path;
    std::string topic;
    std::string note;
    std::string timestamp;

    int mastery;

    // ------------------- //
    topic_entry() = default;

    topic_entry(const std::string& p, const std::string& t, int m, const std::string& n, const std::string& ts)
        : path(p), topic(t), mastery(m), note(n), timestamp(ts) {}
};
