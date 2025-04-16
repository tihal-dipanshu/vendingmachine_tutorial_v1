#!/bin/bash

# Function to make a request to the beverage service
make_request() {
    local city_id=$1
    python3 - << EOF
import sys
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

# Import the service
sys.path.append('./gen-py')
from vending_machine import BeveragePreferenceService
from vending_machine.ttypes import *

try:
    # Make socket
    transport = TSocket.TSocket('localhost', 9092)
    # Buffering is critical. Raw sockets are very slow
    transport = TTransport.TBufferedTransport(transport)
    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    # Create a client to use the protocol encoder
    client = BeveragePreferenceService.Client(protocol)

    # Connect!
    transport.open()

    # For odd city IDs, order COLD beverage, for even city IDs, order HOT beverage
    beverage_type = BeverageType.COLD if $city_id % 2 == 1 else BeverageType.HOT
    result = client.PlaceOrder(beverage_type)
    # Extract just the beverage name from the response
    beverage = result.split('Your ')[1].split(' is ready!')[0]
    print(f"City ID: {$city_id}, Beverage: {beverage}")

    # Close!
    transport.close()

except Thrift.TException as tx:
    print(f"ERROR: {str(tx)}")
EOF
}

# Run for 35 outputs
for city_id in {1..35}; do
    make_request $city_id
done

