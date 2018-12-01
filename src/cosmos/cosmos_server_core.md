



cosmos server core
------------------

a generic server core used by cosmosd and vm's.


architecture
------------

cosmos_server_core

   server config, init
   sockets list
   connections list
   message wrap, send, rcv, unwrap

cosmos_vm_core

   main func
   link vm_ops
   init,run server_core
   cosmos_vfcall_idl


vm_NAME

   vm_abi_adapter_NAME
   vm_ops
   
   


   



theory
------

a service can be generalized simply as:
  - request queue
  - perform service
  - response queue

a generalized server can
  - handle connections
  - receive and format requests
  - format and send responses

service code should be as simple as
  - read request
  - perform service
  - write response

generic service call

  response_msg service_fn( request_msg );


  service_fn( fd );


that is all that needs be defined. that function pointer can be passed to the generic server loop fn.

  server_loop( service_fn );


the generic server gets client connections, reads them, formats a request object and sends to the service function. it gets the response, formats and returns to appropriate client.



generic server init
-------------------

generic server specs

  socket setup
  timeouts


customization 

  message extractor
  server private ptr
  service private ptr


cosmosd and vm as services
--------------------------

define as

  res_t cosmosd( cosmosd_instance, rqmeta, request );

  res_t vm( vm_instance, rqmeta, request );

