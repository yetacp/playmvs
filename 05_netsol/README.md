# About Network Solicitor (NETSOL)
## How to...
- Replace logon screen

## Linux
```bash
$ make # install program in MVS via sockdev
```

## MVS
After submitting run the following to refresh VTAM in hercules:
```
/P TSO
/Z NET,QUICK
/S NET
```