#include "../include/file_storage.hpp"
#include "../include/smart_ptr.hpp"
#include "../include/thread_pool.hpp"

int main(int argc, char **argv) {
  file_storage::TestFileReaderWriter();
  smart_ptr::TestUniquePtr();
  return 0;
}