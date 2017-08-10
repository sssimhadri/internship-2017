msc {
  libpcap, callback, ether_header, queue, hash, 
  "array of linkedlist";
  libpcap => libpcap 
  [ label = "get IPv4 network \n number and netmask" ];
  libpcap => libpcap
  [ label = "open device" ];
  libpcap => libpcap
  [ label = "compile argument to filter"];
  libpcap => libpcap
  [ label = "filter"];
  libpcap => callback
  [label = "process packet"];
  callback => ether_header 
  [label = "get source and \n dest MAC address"];
  ether_header => queue
  [label = "add addresses to queue"];
  queue => hash
  [label = "hash addresses to store \n them in data structure"];
  hash => "array of linkedlist"
  [label = "store hashed addresses"];
  queue => queue
  [label = "delete node after its \n done hashing"];
  queue => queue
  [label = "delete node after its \n done hashing"];  
}
