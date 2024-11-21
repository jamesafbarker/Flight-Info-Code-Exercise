# Flight Information Logger

## Description
This service receives flight information over a UDP message protocol and then saves this data to a database. The message handler is able to accommodate multiple variations of payload versions/data structures. 

## Assumptions and design decisions made
- Multiple messages can be received back-to-back. However, with the current implementation, if a processing of the buffer fails (i.e. an invalid message is parsed) then the buffer is cleared.
- Checksum algorithm is not defined. Currently the validation of the checksum always returns true. This needs to be implemented with a more sophisticated algorithm.
- UDP communication protocol is not implemented currently, as per specification, so the service when run will not receive data.
- Some internal message parsing has been done however more comprehensive error-checking could be done.
- The Database class is currently a dummy class which is supposed to  represent some form of actual database (SQL, save to file).


## Building and Running Project
### Dependencies
- GoogleTest is used for the test framework exampled in this project. This is needed to run the unit tests.

### How to build
This project uses CMake to build the artefact of the project. The following can be run to build the project locally
```
mkdir build
cd build
cmake ..
make
```
To install onto local machine, run the following command. Depending on user permissions, root access may be required to correctly install the service file.
```
make install
```

### How to run
The FlightInfoLogger artefact is deployed as a systemd service. To run as a service:
```
systemctl enable FlightInfoLogger
systemctl daemon-reload
systemctl restart FlightInfoLogger
```

To run locally, call the following:
```
/usr/bin/FlightInfoLogger
```

## Future ideas on implementation (Todo)
- The unique parsers could be separated out into individual libraries. These parsers could then be registered to the PayloadWrapper at the start of the service.
- Create custom command to enable the service and restart the systemd daemon
- Add init_build_script.sh to grab all relevant dependencies for building this project