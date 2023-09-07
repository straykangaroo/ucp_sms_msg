# ucp_sms_msg

Build a UCP/EMI message string for sending a SMS


## Build

```sh
make
```

## Usage

```sh
./ucp_sms_msg <sender number> <recipient number> <message>
```

### Example

```sh
./ucp_sms_msg 01234 56789 Hello
```

output:

```
01/00040/O/01/56789/01234//3/48656C6C6F/31      # with a (not shown) STX (ASCII 0x02) before the string and a (not shown either) ETX (ASCII 0x03) after the string
                                                # A newline is also output after the string, though it is not part of it
```

## License

Distributed under the MIT License. See LICENSE.txt for more information.


## Contact

[https://github.com/straykangaroo/ucp_sms_msg](https://github.com/straykangaroo/ucp_sms_msg)
