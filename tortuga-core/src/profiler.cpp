#include "../inc/TE/profiler.hpp"

#include <algorithm>
#include "../inc/TE/log_utils.hpp"
#include "../inc/TE/logger.hpp"

namespace ta::utils {

AutoProfiler::AutoProfiler(const char *name) {
    mName = std::string(name);
    begin = high_resolution_clock::now();
}

AutoProfiler::~AutoProfiler() {
    auto dt = high_resolution_clock::now() - begin;
    ProfilerService::get().registerSample(mName, (float) dt.count() / 1000000.0f);
}


void ProfilerService::vUpdate() {
    for (auto &entry : lastFrameSamplesMap) {
        auto globalEntry = globalSamplesMap.find(entry.first);
        if (globalEntry == globalSamplesMap.end()) {
            ProfilerGlobalEntry newGlobalSample;
            newGlobalSample.samplesAmount++;
            newGlobalSample.totalDurationMs = entry.second.durationMs;
            newGlobalSample.minDurationMs = entry.second.durationMs;
            newGlobalSample.maxDurationMs = entry.second.durationMs;
            globalSamplesMap.insert(std::make_pair(entry.first, newGlobalSample));
        } else {
            ProfilerGlobalEntry &global = globalEntry->second;
            global.samplesAmount++;
            global.totalDurationMs += entry.second.durationMs;
            global.minDurationMs = std::min(global.minDurationMs, entry.second.durationMs);
            global.maxDurationMs = std::max(global.maxDurationMs, entry.second.durationMs);
        }
    }
    lastFrameSamplesMap.clear();
}


void ProfilerService::registerSample(std::string &name, float durationMs) {
    auto entry = lastFrameSamplesMap.find(name);
    if (entry == lastFrameSamplesMap.end()) {
        lastFrameSamplesMap.insert(make_pair(name, ProfilerFrameEntry{durationMs}));
    } else {
        entry->second.sampleAmount++;
        entry->second.durationMs += durationMs;
    }

}


void ProfilerService::vDestroy() {
    REP_DEBUG("ProfilesManager details", LogChannelFlag::DEFAULT)
    for (auto &entry : globalSamplesMap) {
        REP_DEBUG("  " << entry.first << " [avg: " << entry.second.getAverageDurationMs() << "ms] [min: "
                       << entry.second.minDurationMs << "ms] [max: " << entry.second.maxDurationMs << "ms] ["
                       << entry.second.samplesAmount << " samples]",
                  LogChannelFlag::DEFAULT);
    }
}

}