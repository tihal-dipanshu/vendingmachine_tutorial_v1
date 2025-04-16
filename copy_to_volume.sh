#!/bin/bash

# Create a temporary container to copy files
docker create --name temp_container -v beverage_service_code:/app python:3.6

# Copy the files
docker cp . temp_container:/app/

# Remove the temporary container
docker rm temp_container 