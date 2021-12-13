#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include "gstreamer.pb.h"

using namespace std;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;

void ListPeople(const gstcfg::DataSourceSet _data_source_set);

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const gstcfg::DataSourceSet data_source_set) {
  for (int i = 0; i < data_source_set.data_source_size(); i++) {
    const gstcfg::DataSource& data_source = data_source_set.data_source(i);

    cout << "gst data source ID: " << data_source.gst_id() << endl;
    cout << "gst data source  Name: " << data_source.gst_name() << endl;
  }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  gstcfg::DataSourceSet data_source_set;

  {
    // Read the existing address book.
    int fd = open(argv[1], O_RDONLY);
    FileInputStream* input = new FileInputStream(fd);
    if (!google::protobuf::TextFormat::Parse(input, &data_source_set)) {
      cerr << "Failed to parse gstreamer data source." << endl;
      delete input;
      close(fd);
      return -1;
    }
  }

  ListPeople(data_source_set);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}

