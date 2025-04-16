#!/usr/bin/env python3

import sys
import json
import time
import random
import logging
from concurrent.futures import ThreadPoolExecutor

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

from vending_machine import BeveragePreferenceService
from vending_machine.ttypes import BeverageType, ServiceException, ErrorCode

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class BeveragePreferenceServiceHandler:
    def __init__(self):
        self.logger = logging.getLogger(__name__)
        self.beverages = {
            BeverageType.HOT: ["cappuccino", "latte", "espresso"],
            BeverageType.COLD: ["lemonade", "iced tea", "soda"]
        }

    def PlaceOrder(self, btype):
        try:
            self.logger.info("Received order request for beverage type: %s", btype)
            
            # Select a random beverage of the requested type
            selected_beverage = random.choice(self.beverages[btype])
            response = f"Your {selected_beverage} is ready!"
            
            self.logger.info("Selected beverage: %s", selected_beverage)
            return response
            
        except Exception as e:
            self.logger.error("Error processing order: %s", str(e))
            raise ServiceException(
                errorCode=ErrorCode.SE_THRIFT_HANDLER_ERROR,
                message=str(e)
            )

if __name__ == '__main__':
    handler = BeveragePreferenceServiceHandler()
    processor = BeveragePreferenceService.Processor(handler)
    transport = TSocket.TServerSocket(host='0.0.0.0', port=9092)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TThreadedServer(
        processor,
        transport,
        tfactory,
        pfactory
    )

    logger.info('Starting the beverage preference service...')
    server.serve()
    logger.info('Beverage preference service stopped.') 