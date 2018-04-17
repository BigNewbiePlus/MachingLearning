# coding:utf8
"""
thrift_server.py
"""
import socket
import sys
from hello import HelloService
from hello.ttypes import *

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

class HelloServiceHandler:
    def say(self, msg):
        ret = "Received: " + msg
        print ret
        return ret

handler = HelloServiceHandler()
processor = HelloService.Processor(handler)
transport = TSocket.TServerSocket('localhost', 9090)
tfactory = TTransport.TBufferedTransportFactory()
pfactory = TBinaryProtocol.TBinaryProtocolFactory()

server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

print 'Starting thrift server in python'
server.serve()
print 'done!'


