# frsa

fRSA is a project to create a fingerprint RSA utility.

This means that each public key created will depend both on the private key used to generate it, as well as on a fingerprint of the computer that it was created on. As a result, data encrypted using this public key will only be able to be decrypted on the machine on which it was generated, using the correct private key.
