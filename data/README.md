# AWS IOT Certificates

Put here your

- ca.der
- cert.der
- private.der

## Convert from AWS IOT to DER

```
openssl x509 -in AmazonRootCA1.pem -out ca.der -outform DER
openssl x509 -in *-certificate.pem.crt -out cert.der -outform DER
openssl rsa -in *-private.pem.key -out private.der -outform DER
```
