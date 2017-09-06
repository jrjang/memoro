
#include <string>
#include <cstdint>
#include <vector>

struct __attribute__((packed)) Chunk {
  uint8_t num_reads = 0;
  uint8_t num_writes = 0;
  uint8_t allocated = 0;
  uint8_t pad;
  uint32_t stack_index = 0; // used for file writer
  uint64_t size = 0;
  uint64_t timestamp_start = 0;
  uint64_t timestamp_end = 0;
  uint64_t timestamp_first_access = 0;
  uint64_t timestamp_last_access = 0;
};

struct Trace {
  std::string trace;
  std::vector<Chunk*> chunks;
};

// set the current dataset file, returns dataset stats (num traces, min/max times)
void SetDataset(std::string& file_path);

// add a timestamp interval filter
void SetMinMaxTime(uint64_t max, uint64_t min);
void RemoveMinMaxTime();

// add a trace keyword filter, removing traces containing this from 
void SetTraceKeyword(std::string& keyword);
void RemoveTraceKeyword(std::string& keyword);

// fill times and values with 1000 aggregate data points from whole dataset
// respects filters
void AggregateAll(std::vector<uint64_t>& times, std::vector<uint64_t>& values);

// aggregate chunks of a single stacktrace
void AggregateTrace(std::vector<uint64_t>& times, std::vector<uint64_t>& values, int trace_index);

// get the specified number of chunks starting at the specified indexes
// respects filters
void TraceChunks(std::vector<Chunk>& chunks, int trace_index, int chunk_index, int num_chunks);

// return stacktrace string for given trace
void TraceString(std::string& trace, int trace_index);