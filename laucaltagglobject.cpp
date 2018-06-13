#include "laucaltagglobject.h"

// DEFINE LOOK-UP TABLE
const unsigned char bridgeLutA[512] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
                                        0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                        0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00,
                                        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00,
                                        0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
                                        0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff
                                      };

const unsigned char bridgeLutB[512] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
                                       0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                       0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00,
                                       0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
                                       0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff
                                      };

const unsigned char bridgeLutC[512] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
                                        0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                        0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff,
                                        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                                        0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff,
                                        0xff, 0xff
                                      };

const unsigned char bridgeLutD[512] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
                                        0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                                        0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff,
                                        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                                        0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                                        0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff,
                                        0xff, 0xff
                                      };

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagFilterWidget::LAUCalTagFilterWidget(LAUCalTagGLObject *object, QWidget *parent) : QWidget(parent)
{
    this->setLayout(new QVBoxLayout());
    this->setWindowTitle(QString("LAUCalTag Dialog"));
    this->layout()->setContentsMargins(6, 6, 6, 6);
    this->layout()->setSpacing(10);

    QGroupBox *box = new QGroupBox(QString("Binarize Parameters"));
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    box->setLayout(new QGridLayout());
    box->layout()->setContentsMargins(6, 6, 6, 6);
    ((QGridLayout *)(box->layout()))->setColumnStretch(0, 100);
    ((QGridLayout *)(box->layout()))->setColumnMinimumWidth(2, 160);
    this->layout()->addWidget(box);

    iterSpinBox = new QSpinBox();
    iterSpinBox->setMinimum(1);
    iterSpinBox->setMaximum(5);
    iterSpinBox->setFixedWidth(80);
    iterSpinBox->setAlignment(Qt::AlignRight);
    connect(iterSpinBox, SIGNAL(valueChanged(int)), object, SLOT(onSetIterations(int)));

    QLabel *label = new QLabel(QString("Gaussian Smoother Iterations:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(iterSpinBox, 0, 1, 1, 1, Qt::AlignLeft);

    gausSpinBox = new QSpinBox();
    gausSpinBox->setMinimum(1);
    gausSpinBox->setMaximum(127);
    gausSpinBox->setFixedWidth(80);
    gausSpinBox->setAlignment(Qt::AlignRight);
    connect(gausSpinBox, SIGNAL(valueChanged(int)), object, SLOT(onSetGaussianRadius(int)));

    label = new QLabel(QString("Guassian Smoother Radius:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(gausSpinBox, 0, 3, 1, 1, Qt::AlignLeft);

    offsetSpinBox = new QDoubleSpinBox();
    offsetSpinBox->setMinimum(-1.0);
    offsetSpinBox->setMaximum(1.0);
    offsetSpinBox->setSingleStep(0.01);
    offsetSpinBox->setFixedWidth(80);
    offsetSpinBox->setAlignment(Qt::AlignRight);
    connect(offsetSpinBox, SIGNAL(valueChanged(double)), object, SLOT(onSetOffset(double)));

    label = new QLabel(QString("Gaussian Filter Offset:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(offsetSpinBox, 1, 1, 1, 1, Qt::AlignLeft);

    mednSpinBox = new QSpinBox();
    mednSpinBox->setMinimum(0);
    mednSpinBox->setMaximum(127);
    mednSpinBox->setFixedWidth(80);
    mednSpinBox->setAlignment(Qt::AlignRight);
    connect(mednSpinBox, SIGNAL(valueChanged(int)), object, SLOT(onSetMedianRadius(int)));

    label = new QLabel(QString("Median Smoother Radius:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(mednSpinBox, 1, 3, 1, 1, Qt::AlignLeft);

    box = new QGroupBox(QString("CalTag Parameters"));
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    box->setLayout(new QGridLayout());
    box->layout()->setContentsMargins(6, 6, 6, 6);
    ((QGridLayout *)(box->layout()))->setColumnStretch(0, 100);
    ((QGridLayout *)(box->layout()))->setColumnMinimumWidth(2, 160);
    this->layout()->addWidget(box);

    minRegionArea = new QSpinBox();
    minRegionArea->setMinimum(0);
    minRegionArea->setMaximum(1000000);
    minRegionArea->setValue(128 - 32);
    minRegionArea->setFixedWidth(80);
    connect(minRegionArea, SIGNAL(valueChanged(int)), object, SLOT(onSetMinRegionArea(int)));

    label = new QLabel(QString("Minimum Region Area:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(minRegionArea, 0, 1, 1, 1, Qt::AlignLeft);

    maxRegionArea = new QSpinBox();
    maxRegionArea->setMinimum(0);
    maxRegionArea->setMaximum(1000000);
    maxRegionArea->setValue((640 * 480) / 16);
    maxRegionArea->setFixedWidth(80);
    connect(maxRegionArea, SIGNAL(valueChanged(int)), object, SLOT(onSetMaxRegionArea(int)));

    label = new QLabel(QString("Maximum Region Area:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 0, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(maxRegionArea, 0, 3, 1, 1, Qt::AlignLeft);

    minBoxCount = new QSpinBox();
    minBoxCount->setMinimum(0);
    minBoxCount->setMaximum(1000000);
    minBoxCount->setValue(128);
    minBoxCount->setFixedWidth(80);
    connect(minBoxCount, SIGNAL(valueChanged(int)), object, SLOT(onSetMinBoxCount(int)));

    label = new QLabel(QString("Minimum Box Count:"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 0, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(minBoxCount, 1, 1, 1, 1, Qt::AlignLeft);

    flipCalTagsFlag = new QCheckBox();
    flipCalTagsFlag->setCheckable(true);
    flipCalTagsFlag->setChecked(false);
    flipCalTagsFlag->setFixedWidth(80);
    connect(flipCalTagsFlag, SIGNAL(toggled(bool)), object, SLOT(onSetFlipCalTagsFlag(bool)));

    label = new QLabel(QString("Flip CalTag (backlight):"));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setAlignment(Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(label, 1, 2, 1, 1, Qt::AlignRight);
    ((QGridLayout *)(box->layout()))->addWidget(flipCalTagsFlag, 1, 3, 1, 1, Qt::AlignLeft);

    // SET THE INITIAL VALUES FROM THE SUPPLIED GLOBJECT
    iterSpinBox->setValue(object->iterations());
    gausSpinBox->setValue(object->gaussianRadius());
    mednSpinBox->setValue(object->medianRadius());
    offsetSpinBox->setValue(object->offset());

    minRegionArea->setValue(object->minRegion());
    maxRegionArea->setValue(object->maxRegion());
    minBoxCount->setValue(object->minBox());
    flipCalTagsFlag->setChecked(object->flipCalTags());
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagFilterWidget::load()
{
    // LOAD THE PARAMETERS FROM SETTINGS
    QSettings settings;

    iterSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::iterSpinBox"), iterSpinBox->value()).toInt());
    gausSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::gausSpinBox"), gausSpinBox->value()).toInt());
    mednSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::mednSpinBox"), mednSpinBox->value()).toInt());
    offsetSpinBox->setValue(settings.value(QString("LAUCalTagScanWidget::offsetSpinBox"), offsetSpinBox->value()).toDouble());

    minRegionArea->setValue(settings.value(QString("LAUCalTagScanWidget::minRegionArea"), minRegionArea->value()).toInt());
    maxRegionArea->setValue(settings.value(QString("LAUCalTagScanWidget::maxRegionArea"), maxRegionArea->value()).toInt());
    minBoxCount->setValue(settings.value(QString("LAUCalTagScanWidget::minBoxCount"), minBoxCount->value()).toInt());
    flipCalTagsFlag->setChecked(settings.value(QString("LAUCalTagScanWidget::flipCalTagsFlag"), flipCalTagsFlag->isChecked()).toBool());
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagFilterWidget::save()
{
    // LOAD THE PARAMETERS FROM SETTINGS
    QSettings settings;

    settings.setValue(QString("LAUCalTagScanWidget::iterSpinBox"), iterSpinBox->value());
    settings.setValue(QString("LAUCalTagScanWidget::gausSpinBox"), gausSpinBox->value());
    settings.setValue(QString("LAUCalTagScanWidget::mednSpinBox"), mednSpinBox->value());
    settings.setValue(QString("LAUCalTagScanWidget::offsetSpinBox"), offsetSpinBox->value());

    settings.setValue(QString("LAUCalTagScanWidget::minRegionArea"), minRegionArea->value());
    settings.setValue(QString("LAUCalTagScanWidget::maxRegionArea"), maxRegionArea->value());
    settings.setValue(QString("LAUCalTagScanWidget::minBoxCount"), minBoxCount->value());
    settings.setValue(QString("LAUCalTagScanWidget::flipCalTagsFlag"), flipCalTagsFlag->isChecked());
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagGLObject::LAUCalTagGLObject(QObject *parent) : QObject(parent), isValidFlag(false)
{
    // INITIALIZE PRIVATE VARIABLES
    textureLUT = NULL;

    frameBufferObjectA = NULL;
    frameBufferObjectB = NULL;
    frameBufferObjectC = NULL;
    frameBufferObjectD = NULL;

    quantizationOffset = -0.01f;
    medianFilterRadius = 0;
    gaussianFilterRadius = 10;
    iterationCount = 1;

    // INITIALIZE CLASS VARIABLES
    minBoxCount     = 32;                   // 2X2 PIXELS TIMES 8X8 BOX SIZE
    maxRegionArea   = (640 * 480) / 16;     // NEEDS IMAGE SIZE AND BYTES PER PIXEL
    minRegionArea   = maxRegionArea / 10;
    flipCalTagsFlag = false;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUCalTagGLObject::~LAUCalTagGLObject()
{
    if (textureLUT) {
        delete textureLUT;
    }

    if (frameBufferObjectA) {
        delete frameBufferObjectA;
    }

    if (frameBufferObjectB) {
        delete frameBufferObjectB;
    }

    if (frameBufferObjectC) {
        delete frameBufferObjectC;
    }

    if (frameBufferObjectD) {
        delete frameBufferObjectD;
    }

    qDebug() << "LAUCalTagGLObject::~LAUCalTagGLObject()";
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::initializeGL()
{
    // INITIALIZE OUR GL CALLS AND SET THE CLEAR COLOR
    initializeOpenGLFunctions();

    // CREATE VERTEX BUFFER TO HOLD CORNERS OF QUADRALATERAL
    quadVertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    quadVertexBuffer.create();
    quadVertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (quadVertexBuffer.bind()) {
        // ALLOCATE THE VERTEX BUFFER FOR HOLDING THE FOUR CORNERS OF A RECTANGLE
        quadVertexBuffer.allocate(16 * sizeof(float));
        float *buffer = (float *)quadVertexBuffer.map(QOpenGLBuffer::WriteOnly);
        if (buffer) {
            buffer[0]  = -1.0;
            buffer[1]  = -1.0;
            buffer[2]  = 0.0;
            buffer[3]  = 1.0;
            buffer[4]  = +1.0;
            buffer[5]  = -1.0;
            buffer[6]  = 0.0;
            buffer[7]  = 1.0;
            buffer[8]  = +1.0;
            buffer[9]  = +1.0;
            buffer[10] = 0.0;
            buffer[11] = 1.0;
            buffer[12] = -1.0;
            buffer[13] = +1.0;
            buffer[14] = 0.0;
            buffer[15] = 1.0;
            quadVertexBuffer.unmap();
        } else {
            qDebug() << QString("quadVertexBuffer not allocated.") << glGetError();
        }
        quadVertexBuffer.release();
    }

    // CREATE INDEX BUFFER TO ORDERINGS OF VERTICES FORMING POLYGON
    quadIndexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    quadIndexBuffer.create();
    quadIndexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (quadIndexBuffer.bind()) {
        quadIndexBuffer.allocate(6 * sizeof(unsigned int));
        unsigned int *indices = (unsigned int *)quadIndexBuffer.map(QOpenGLBuffer::WriteOnly);
        if (indices) {
            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
            indices[3] = 0;
            indices[4] = 2;
            indices[5] = 3;
            quadIndexBuffer.unmap();
        } else {
            qDebug() << QString("indiceBufferA buffer mapped from GPU.");
        }
        quadIndexBuffer.release();
    }

    // CREATE A TEXTURE FOR LOOK UP OPERATIONS
    textureLUT = new QOpenGLTexture(QOpenGLTexture::Target1D);
    textureLUT->setSize(512);
    textureLUT->setFormat(QOpenGLTexture::RGBA32F);
    textureLUT->setWrapMode(QOpenGLTexture::ClampToBorder);
    textureLUT->setMinificationFilter(QOpenGLTexture::Nearest);
    textureLUT->setMagnificationFilter(QOpenGLTexture::Nearest);
    textureLUT->allocateStorage();

    // NOW ADD OUR LIST OF HARRIS CORNER SHADER PROGRAMS
    setlocale(LC_NUMERIC, "C");
    programA.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterRGBAtoGray.vert");
    programA.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterRGBAtoGray.frag");
    programA.link();

    programB.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterXGaussian.vert");
    programB.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterXGaussian.frag");
    programB.link();

    programC.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterYGaussian.vert");
    programC.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterYGaussian.frag");
    programC.link();

    programD.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterAdaptiveThreshold.vert");
    programD.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterAdaptiveThreshold.frag");
    programD.link();

    programE.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterBinaryMedian.vert");
    programE.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterBinaryMedian.frag");
    programE.link();

    programF.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterSobelEdge.vert");
    programF.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterSobelEdge.frag");
    programF.link();

    programG.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterBinaryLookUpTable.vert");
    programG.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterBinaryLookUpTable.frag");
    programG.link();

    programH.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterMaxRGBA.vert");
    programH.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterMaxRGBA.frag");
    programH.link();

    programI.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/filterMinRGBA.vert");
    programI.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/filterMinRGBA.frag");
    programI.link();

    programJ.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/calTagXYZW.vert");
    programJ.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/calTagXYZW.frag");
    programJ.link();

    programK.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/Shaders/displayCalTag.vert");
    programK.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Shaders/displayCalTag.frag");
    programK.link();
    setlocale(LC_ALL, "");

    // SET THE VALID TAG TRUE SO WE CAN TEST IF INITIALIZED
    isValidFlag = true;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::processGL(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *outputFBO)
{
    if (isValid()) {
        // SEE IF WE NEED NEW FBOS
        testFBO(&frameBufferObjectA, videoTexture->width(), videoTexture->height());
        testFBO(&frameBufferObjectB, videoTexture->width(), videoTexture->height());
        testFBO(&frameBufferObjectC, videoTexture->width(), videoTexture->height());
        testFBO(&frameBufferObjectD, videoTexture->width(), videoTexture->height());

        // RESIZE THE BYTE ARRAYS AS NEEDED
        if (memoryObject[0].width() != (unsigned int)videoTexture->width() || memoryObject[0].height() != (unsigned int)videoTexture->height()) {
            memoryObject[0] = LAUMemoryObject(videoTexture->width(), videoTexture->height(), 1, sizeof(unsigned char));
            memoryObject[1] = LAUMemoryObject(videoTexture->width(), videoTexture->height(), 1, sizeof(unsigned char));
#ifdef QT_DEBUG
            debugObject = LAUMemoryObject(videoTexture->width(), videoTexture->height(), 3, sizeof(unsigned char));
#endif
        }

        // BINARIZE THE INCOMING BUFFER
        binarize(videoTexture, frameBufferObjectA, frameBufferObjectB, frameBufferObjectC);
        sobel(frameBufferObjectC, frameBufferObjectB);
        cleanUp(frameBufferObjectB, frameBufferObjectA);
        //dilationErosion(frameBufferObjectA, frameBufferObjectB);

        // DOWNLOAD THE RESULTING BINARY TEXTURE TO OUR MEMORY BUFFER FOR FURTHER PROCESSING
        glBindTexture(GL_TEXTURE_2D, frameBufferObjectA->texture());
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, (unsigned char *)memoryObject[0].constPointer());

        glBindTexture(GL_TEXTURE_2D, frameBufferObjectC->texture());
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, (unsigned char *)memoryObject[1].constPointer());

        // LOOK FOR CALTAGS AND GET THE CR TO XYZ TRANSFORM
        bool okay = false;
#ifdef QT_DEBUG
        glBindTexture(GL_TEXTURE_2D, frameBufferObjectA->texture());
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *)debugObject.constPointer());
        cv::Mat transform = detectCalTagGrid(memoryObject[0], memoryObject[1], debugObject, minBoxCount, minRegionArea, maxRegionArea, flipCalTagsFlag, gridPairings, &okay);
#else
        cv::Mat transform = detectCalTagGrid(memoryObject[0], memoryObject[1], minBoxCount, minRegionArea, maxRegionArea, flipCalTagsFlag, gridPairings, &okay);
#endif
        float transformAsVector[30];
        for (int n = 0; n < 30; n++) {
            transformAsVector[n] = (float)transform.at<double>(n);
        }
        qDebug() << transformAsVector[0];

        // DRAW THE BEST-FIT XY PLANE TO SCREEN WITH THE BINARY IMAGE
        if (frameBufferObjectB && frameBufferObjectB->bind()) {
            if (programJ.bind()) {
                // CLEAR THE FRAME BUFFER OBJECT
                glViewport(0, 0, frameBufferObjectB->width(), frameBufferObjectB->height());
                glClearColor(NAN, NAN, NAN, NAN);
                glClear(GL_COLOR_BUFFER_BIT);

                // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
                if (quadVertexBuffer.bind()) {
                    if (quadIndexBuffer.bind()) {
                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, frameBufferObjectC->texture());
                        programJ.setUniformValue("qt_texture", 0);

                        // SET THE TRANSFORM PARAMETERS ON THE SHADER
                        programJ.setUniformValue("qt_offset", QPointF((float)frameBufferObjectB->width() / 2.0f, (float)frameBufferObjectB->height() / 2.0f));
                        programJ.setUniformValueArray("qt_transform", transformAsVector, 30, 1);

                        // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                        glVertexAttribPointer(programJ.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                        programJ.enableAttributeArray("qt_vertex");
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                        // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                        quadIndexBuffer.release();
                    }
                    quadVertexBuffer.release();
                }
                programJ.release();
            }
            frameBufferObjectB->release();
        }

        // COPY THE LOCAL FRAME BUFFER OBJECT TO THE USER SUPPLIED BUFFER
        if (outputFBO) {
            QOpenGLFramebufferObject::blitFramebuffer(outputFBO, frameBufferObjectB);
        }
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::testFBO(QOpenGLFramebufferObject *fbo[], int cols, int rows)
{
    if ((*fbo) == NULL) {
        // CREATE A FORMAT OBJECT FOR CREATING THE FRAME BUFFER
        QOpenGLFramebufferObjectFormat frameBufferObjectFormat;
        frameBufferObjectFormat.setInternalTextureFormat(GL_RGBA32F);

        (*fbo) = new QOpenGLFramebufferObject(cols, rows, frameBufferObjectFormat);
        (*fbo)->release();
    } else if ((*fbo)->width() != cols || (*fbo)->height() != rows) {
        delete (*fbo);

        // CREATE A FORMAT OBJECT FOR CREATING THE FRAME BUFFER
        QOpenGLFramebufferObjectFormat frameBufferObjectFormat;
        frameBufferObjectFormat.setInternalTextureFormat(GL_RGBA32F);

        (*fbo) = new QOpenGLFramebufferObject(cols, rows, frameBufferObjectFormat);
        (*fbo)->release();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::binarize(QOpenGLTexture *videoTexture, QOpenGLFramebufferObject *fboA, QOpenGLFramebufferObject *fboB, QOpenGLFramebufferObject *fboC)
{
    // BIND THE FRAME BUFFER OBJECT FOR PROCESSING
    if (fboA && fboA->bind()) {
        if (programA.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fboA->width(), fboA->height());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE0);
                    videoTexture->bind();
                    programA.setUniformValue("qt_texture", 0);

                    // Tell OpenGL programAmable pipeline how to locate vertex position data
                    glVertexAttribPointer(programA.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programA.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programA.release();
        }
        fboA->release();
    }

    // COPY THE RESCALED IMAGE BACK TO FRAME BUFFER OBJECT A TO FBO C
    QOpenGLFramebufferObject::blitFramebuffer(fboC, fboA);

    for (unsigned int iter = 0; iter < iterationCount; iter++) {
        // APPLY A GAUSSIAN FILTER IN THE X-DIRECTION TO THE FBOC TO FBOD
        if (fboB && fboB->bind()) {
            if (programB.bind()) {
                // CLEAR THE FRAME BUFFER OBJECT
                glViewport(0, 0, fboB->width(), fboB->height());
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
                if (quadVertexBuffer.bind()) {
                    if (quadIndexBuffer.bind()) {
                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE1);
                        glBindTexture(GL_TEXTURE_2D, fboC->texture());
                        programB.setUniformValue("qt_texture", 1);

                        // TELL THE SHADER HOW MANY PIXELS WIDE TO APPLY GAUSSIAN FILTER
                        programB.setUniformValue("qt_width", (int)gaussianFilterRadius);

                        // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                        glVertexAttribPointer(programB.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                        programB.enableAttributeArray("qt_vertex");
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                        // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                        quadIndexBuffer.release();
                    }
                    quadVertexBuffer.release();
                }
                programB.release();
            }
            fboB->release();
        }

        // APPLY A GAUSSIAN FILTER IN THE Y-DIRECTION TO THE FBOD TO FBOC
        if (fboC && fboC->bind()) {
            if (programC.bind()) {
                // CLEAR THE FRAME BUFFER OBJECT
                glViewport(0, 0, fboC->width(), fboC->height());
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
                if (quadVertexBuffer.bind()) {
                    if (quadIndexBuffer.bind()) {
                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE2);
                        glBindTexture(GL_TEXTURE_2D, fboB->texture());
                        programC.setUniformValue("qt_texture", 2);

                        // TELL THE SHADER HOW MANY PIXELS WIDE TO APPLY GAUSSIAN FILTER
                        programC.setUniformValue("qt_width", (int)gaussianFilterRadius);

                        // Tell OpenGL programmable pipeline how to locate vertex position data
                        glVertexAttribPointer(programC.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                        programC.enableAttributeArray("qt_vertex");
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                        // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                        quadIndexBuffer.release();
                    }
                    quadVertexBuffer.release();
                }
                programC.release();
            }
            fboC->release();
        }
    }

    // APPLY THRESHOLD OF FBOA BY SMOOTHED IMAGE FBOC
    if (fboB && fboB->bind()) {
        if (programD.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fboB->width(), fboB->height());
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, fboA->texture());
                    programD.setUniformValue("qt_texture", 3);

                    // BIND THE THRESHOLD FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, fboC->texture());
                    programD.setUniformValue("qt_threshold", 1);
                    programD.setUniformValue("qt_invert", false);

                    // SET THE FLOATING POINT OFFSET FOR QUANTIZATION
                    programD.setUniformValue("qt_offset", quantizationOffset);

                    // Tell OpenGL programmable pipeline how to locate vertex position data
                    glVertexAttribPointer(programD.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programD.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programD.release();
        }
        fboB->release();
    }

    // APPLY A MEDIAN FILTER TO THE BINARY IMAGE
    if (medianFilterRadius > 0) {
        if (fboC && fboC->bind()) {
            if (programE.bind()) {
                // CLEAR THE FRAME BUFFER OBJECT
                glViewport(0, 0, fboC->width(), fboC->height());
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
                if (quadVertexBuffer.bind()) {
                    if (quadIndexBuffer.bind()) {
                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE4);
                        glBindTexture(GL_TEXTURE_2D, fboB->texture());
                        programE.setUniformValue("qt_texture", 4);

                        // SET THE MEDIAN FILTER RADIUS
                        programE.setUniformValue("qt_radius", (int)medianFilterRadius);
                        programE.setUniformValue("qt_threshold", (float)((2 * medianFilterRadius + 1) * (2 * medianFilterRadius + 1)) / 2.0f);

                        // Tell OpenGL programmable pipeline how to locate vertex position data
                        glVertexAttribPointer(programE.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                        programE.enableAttributeArray("qt_vertex");
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                        // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                        quadIndexBuffer.release();
                    }
                    quadVertexBuffer.release();
                }
                programE.release();
            }
            fboC->release();
        }
    } else {
        // COPY THE RESCALED IMAGE BACK TO FRAME BUFFER OBJECT A TO FBO C
        QOpenGLFramebufferObject::blitFramebuffer(fboC, fboB);
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::sobel(QOpenGLFramebufferObject *fboA, QOpenGLFramebufferObject *fboB)
{
    // APPLY A SOBEL EDGE DETECTING FILTER TO THE BINARY IMAGE
    if (fboB && fboB->bind()) {
        if (programF.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(0, 0, fboB->width(), fboB->height());
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE5);
                    glBindTexture(GL_TEXTURE_2D, fboA->texture());
                    programF.setUniformValue("qt_texture", 5);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    glVertexAttribPointer(programF.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programF.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programF.release();
        }
        fboB->release();
    }
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::cleanUp(QOpenGLFramebufferObject *fboA, QOpenGLFramebufferObject *fboB)
{
    for (int n = 0; n < 4; n++) {
        QOpenGLFramebufferObject *inFBO = NULL;
        QOpenGLFramebufferObject *otFBO = NULL;

        switch (n) {
            case 0:
                inFBO = fboA;
                otFBO = fboB;
                textureLUT->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, (const void *)bridgeLutA);
                break;
            case 1:
                inFBO = fboA;
                otFBO = fboB;
                textureLUT->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, (const void *)bridgeLutB);
                break;
            case 2:
                inFBO = fboB;
                otFBO = fboA;
                textureLUT->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, (const void *)bridgeLutC);
                break;
            case 3:
                inFBO = fboA;
                otFBO = fboB;
                textureLUT->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, (const void *)bridgeLutD);
                break;
        }

        // APPLY A BRIDGE BINARY FILTER TO THE BINARY IMAGE
        if (otFBO && otFBO->bind()) {
            if (programG.bind()) {
                // CLEAR THE FRAME BUFFER OBJECT
                glViewport(1, 1, otFBO->width() - 2, otFBO->height() - 2);
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
                if (quadVertexBuffer.bind()) {
                    if (quadIndexBuffer.bind()) {
                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE6);
                        glBindTexture(GL_TEXTURE_2D, inFBO->texture());
                        programG.setUniformValue("qt_texture", 6);

                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE7);
                        textureLUT->bind();
                        programG.setUniformValue("qt_lookUpTable", 7);

                        // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                        glVertexAttribPointer(programG.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                        programG.enableAttributeArray("qt_vertex");
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                        // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                        quadIndexBuffer.release();
                    }
                    quadVertexBuffer.release();
                }
                programG.release();
            }
            otFBO->release();
        }

        if (n == 0 && inFBO && inFBO->bind()) {
            if (programE.bind()) {
                // CLEAR THE FRAME BUFFER OBJECT
                glViewport(0, 0, inFBO->width(), inFBO->height());
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
                if (quadVertexBuffer.bind()) {
                    if (quadIndexBuffer.bind()) {
                        // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                        glActiveTexture(GL_TEXTURE4);
                        glBindTexture(GL_TEXTURE_2D, otFBO->texture());
                        programE.setUniformValue("qt_texture", 4);

                        // SET THE MEDIAN FILTER RADIUS
                        programE.setUniformValue("qt_radius", 1);
                        programE.setUniformValue("qt_threshold", 4.5f);

                        // Tell OpenGL programmable pipeline how to locate vertex position data
                        glVertexAttribPointer(programE.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                        programE.enableAttributeArray("qt_vertex");
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                        // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                        quadIndexBuffer.release();
                    }
                    quadVertexBuffer.release();
                }
                programE.release();
            }
            inFBO->release();
        }
    }

    // COPY THE RESCALED IMAGE BACK TO FRAME BUFFER OBJECT B
    QOpenGLFramebufferObject::blitFramebuffer(fboB, fboA);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::dilationErosion(QOpenGLFramebufferObject *fboA, QOpenGLFramebufferObject *fboB)
{
    // APPLY EROSION AS THE MIN FILTER OPERATION
    if (fboB && fboB->bind()) {
        if (programH.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(1, 1, fboB->width() - 2, fboB->height() - 2);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, fboA->texture());
                    programH.setUniformValue("qt_texture", 0);

                    // SET THE MEDIAN FILTER RADIUS
                    programH.setUniformValue("qt_radius", 1);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    glVertexAttribPointer(programH.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programH.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programH.release();
        }
        fboB->release();
    }

    // APPLY DILATION AS THE MAX FILTER OPERATION
    if (fboA && fboA->bind()) {
        if (programI.bind()) {
            // CLEAR THE FRAME BUFFER OBJECT
            glViewport(1, 1, fboA->width() - 2, fboA->height() - 2);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // BIND VBOS FOR DRAWING TRIANGLES ON SCREEN
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // BIND THE TEXTURE FROM THE FRAME BUFFER OBJECT
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, fboB->texture());
                    programI.setUniformValue("qt_texture", 0);

                    // SET THE MEDIAN FILTER RADIUS
                    programI.setUniformValue("qt_radius", 1);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    glVertexAttribPointer(programI.attributeLocation("qt_vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                    programI.enableAttributeArray("qt_vertex");
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    // RELEASE THE FRAME BUFFER OBJECT AND ITS ASSOCIATED GLSL PROGRAMS
                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programI.release();
        }
        fboA->release();
    }

    // COPY THE RESCALED IMAGE BACK TO FRAME BUFFER OBJECT B
    // QOpenGLFramebufferObject::blitFramebuffer(fboA, fboB);
}

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
#ifdef QT_DEBUG
cv::Mat LAUCalTagGLObject::detectCalTagGrid(LAUMemoryObject sbObj, LAUMemoryObject inObj, LAUMemoryObject dbObj, int minBoxes, int minRegion, int maxRegion, bool flipCalTags, QList<Pairing> &pairings, bool *okay)
#else
cv::Mat LAUCalTagGLObject::detectCalTagGrid(LAUMemoryObject sbObj, LAUMemoryObject inObj, int minBoxes, int minRegion, int maxRegion, bool flipCalTags, QList<Pairing> &pairings, bool *okay)
#endif
{
    qDebug() << minBoxes << minRegion << maxRegion << flipCalTags;

    // CLEAR THE GRID PAIRINGS FROM ANY PREVIOUS CALL
    pairings.clear();

    // CREATE A RETURN MATRIX
    cv::Mat localTransform(1, 30, CV_64F);

    // CREATE CV::MAT WRAPPER AROUND OUR MEMORY OBJECT
    cv::Mat sbImage(sbObj.height(), sbObj.width(), CV_8UC1, (unsigned char *)sbObj.constPointer(), sbObj.step());
    cv::Mat inImage(inObj.height(), inObj.width(), CV_8UC1, (unsigned char *)inObj.constPointer(), inObj.step());
#ifdef QT_DEBUG
    cv::Mat dbImage(dbObj.height(), dbObj.width(), CV_8UC3, (unsigned char *)dbObj.constPointer(), dbObj.step());
#endif

    // FIND QUADRILATERALS IN THE SOBEL EDGE IMAGE
    cv::vector<cv::vector<cv::Point2f>> quads = quadArea(sbImage, minRegion, maxRegion);

    // GET A GOOD APPROXIMATION OF WHERE THE SADDLE POINTS ARE
    quads = findSaddles(quads);

    // DECODE THE CALTAG SQUARES
    cv::vector<cv::vector<cv::Point2f>> coordinates = findPattern(inImage, quads, flipCalTags);

#ifdef QT_DEBUG
    for (unsigned int n = 0; n < coordinates.size(); n++) {
        for (unsigned int m = 0; m < coordinates[n].size(); m++) {
            if (qIsNaN(coordinates[n][m].x * coordinates[n][m].y) == false) {
                cv::circle(dbImage, quads[n][m], 4, cv::Scalar(255, 255, 0), -1);
            }
        }
    }
    //cv::imshow("", dbImage);
#endif

    // MAKE SURE WE HAVE ENOUGH DETECTED RECTANGLES
    if (quads.size() > (unsigned long)minBoxes) {
        // PRINT OUT A REPORT ON HOW IMAGE SQUARES ARE ALIGNED AND HOW THEY GET MAPPED TO CALTAG SQUARES
        //QFile file(QString("/tmp/squaresReport.txt"));
        //if (file.open(QIODevice::WriteOnly)) {
        //    QTextStream stream(&file);
        //    for (unsigned int n = 0; n < squares.size(); n++) {
        //        for (int c = 0; c < 4; c++) {
        //            stream << QString("%1, %2, %3, %4\n").arg(squares[n][c].x).arg(squares[n][c].y).arg(coordinates[n][c].x).arg(coordinates[n][c].y);
        //        }
        //    }
        //    file.close();
        //}

        // DELETE INVALID SQUARES WHILE ACCUMULATING POINTS FROM IMAGE TO GRID SPACE
        cv::vector<cv::Point2f> toPoints, fmPoints;
        for (unsigned int i = 0; i < coordinates.size(); i++) {
            for (unsigned int j = 0; j < 4; j++) {
                // SEE IF THIS COORDINATE IS A NAN
                if (qIsNaN(coordinates[i][j].x * coordinates[i][j].y) == false) {
                    fmPoints.push_back(quads[i][j]);
                    toPoints.push_back(coordinates[i][j]);
                }
            }
        }

        // LETS REMOVE OUTLIERS FROM OUR FMPOINTS BY USING A LINEAR MAPPING BETWEEN THE TWO
        removeOutlierPoints(fmPoints, toPoints);

        // MAKE SURE WE HAVE ENOUGH DETECTED POINTS
        if (toPoints.size() > (unsigned long)minBoxes) {
            // MAKE A LOCAL COPY OF THE POINT PAIRINGS
            for (unsigned int n = 0; n < toPoints.size() && n < fmPoints.size(); n++) {
                Pairing pairing;
                pairing.cr = QPoint(fmPoints[n].x, fmPoints[n].y);
                pairing.xy = QPoint(toPoints[n].x, toPoints[n].y);
                pairings << pairing;
            }

            // FIND BEST TRANSFORM FROM CAMERA TO CALIBRATION WORLD COORDINATES
            localTransform = findBestQuadraticMapping(fmPoints, toPoints, inObj.width(), inObj.height(), CALTAGPOLYNOMIALORDER);
            if (okay) {
                *okay = true;
            }
        } else {
            // SET THE TRANSFORM TO AN INVALID MATRIX
            localTransform.setTo(NAN);
            if (okay) {
                *okay = false;
            }
        }
    } else {
        // SET THE TRANSFORM TO AN INVALID MATRIX
        localTransform.setTo(NAN);
        if (okay) {
            *okay = false;
        }
    }
    return (localTransform);
}

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
cv::vector<cv::vector<cv::Point2f>> LAUCalTagGLObject::quadArea(cv::Mat sbImage, int minArea, int maxArea)
{
    // CREATE ASSOCIATED DATA STRUCTURES TO HOLD INTERMEDIATE RESULTS
    cv::vector<cv::vector<cv::Point>> contours;
    cv::vector<cv::Vec4i> hierarchy;

    // SEARCH AND STORE ANY CONTOURS IN THE IMAGE
    cv::findContours(sbImage.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));

    cv::vector<cv::vector<cv::Point>> contoursPoly;
    cv::vector<cv::vector<cv::Point2f>> quadrilaterals;

    // FOR EACH CONTOUR, APPROXIMATE IT WITH A POLYGON
    for (unsigned int i = 0; i < contours.size(); ++i) {
        contoursPoly.push_back(contours[i]);
        cv::approxPolyDP(contours[i], contoursPoly[i], 3.0, true);
        if (contoursPoly[i].size() == 4 && cv::isContourConvex(contoursPoly[i])) {
            int area = cv::contourArea(contoursPoly[i]);
            if (area > minArea && area < maxArea) {
                quadrilaterals.push_back(sortPoints(contoursPoly[i]));
            }
        }
    }

    return (quadrilaterals);
}

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
cv::vector<cv::vector<cv::Point2f>> LAUCalTagGLObject::findSaddles(cv::vector<cv::vector<cv::Point2f>> quads)
{
    QList<unsigned int> indices;
    for (unsigned int m = 0; m < 4 * quads.size(); m++) {
        cv::Point2f meanPt(0.0f, 0.0f);
        for (unsigned int n = m; n < 4 * quads.size(); n++) {
            if (LAUCalTagGLObject::length(quads[m / 4][m % 4] - quads[n / 4][n % 4]) < 5.0f) {
                meanPt = meanPt + quads[n / 4][n % 4];
                indices << n;
            }
        }
        if (indices.size() > 0) {
            meanPt = meanPt / indices.size();
            while (indices.size() > 0) {
                unsigned int n = indices.takeLast();
                quads[n / 4][n % 4] = meanPt;
            }
        }
    }

    return (quads);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
cv::vector<cv::vector<cv::Point2f>> LAUCalTagGLObject::findPattern(cv::Mat inImage, cv::vector<cv::vector<cv::Point2f>> squares, bool flipCalTags)
{
    // CREATE OUTPUT DATA STRUCTURE
    cv::vector<cv::vector<cv::Point2f>> outputSquares;

    // MAKE LIST OF SQUARE SPACE COORDINATES FOR A SINGLE SQUARE
    cv::vector<cv::Point2f> sqPoints;
    sqPoints.push_back(cv::Point2f(0.0f, 0.0f));
    sqPoints.push_back(cv::Point2f(1.0f, 0.0f));
    sqPoints.push_back(cv::Point2f(1.0f, 1.0f));
    sqPoints.push_back(cv::Point2f(0.0f, 1.0f));

    // MAKE LIST OF SQUARE SPACE COORDINATES FOR CODED BITS
    cv::vector<cv::Point3f> gdPoints, kgPoints;
    gdPoints.push_back(cv::Point3f(0.6875f, 0.6875f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.6875f, 0.5625f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.6875f, 0.4375f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.6875f, 0.3125f, 1.0f));

    gdPoints.push_back(cv::Point3f(0.5625f, 0.6875f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.5625f, 0.5625f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.5625f, 0.4375f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.5625f, 0.3125f, 1.0f));

    gdPoints.push_back(cv::Point3f(0.4375f, 0.6875f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.4375f, 0.5625f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.4375f, 0.4375f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.4375f, 0.3125f, 1.0f));

    gdPoints.push_back(cv::Point3f(0.3125f, 0.6875f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.3125f, 0.5625f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.3125f, 0.4375f, 1.0f));
    gdPoints.push_back(cv::Point3f(0.3125f, 0.3125f, 1.0f));

    // CREATE DECODING MATRIX FOR LATER
    cv::Mat decodingMatrix(4, 4, CV_32S);
    for (unsigned int i = 0; i < 16; i++) {
        decodingMatrix.at<int>(i / 4, i % 4) = qRound(pow(2.0, (double)i));
    }

    // NOW LET'S TRY ALL ORIENTATIONS TO SEE WHICH IS THE MOST LIKELY ORIENTATION
    int hist[4] = { 0, 0, 0, 0};
    for (unsigned int n = 0; n < squares.size(); n++) {
        // DERIVE SQUARE COORDINATES TO IMAGE PIXEL COORDINATES BASED ON CURRENT SQUARE
        cv::vector<cv::Point2f> inPoints;
        for (int c = 0; c < 4; c++) {
            inPoints.push_back(squares[n][c]);
        }
        cv::Mat localTransform = cv::getPerspectiveTransform(sqPoints, inPoints);

        // MAP THE CODE BIT COORDINATES TO IMAGE PIXEL COORDINATES
        cv::Mat codeMatrix(4, 4, CV_32S);
        cv::transform(gdPoints, kgPoints, localTransform);
        for (unsigned int i = 0; i < kgPoints.size(); i++) {
            // ACCUMULATE THE SUM OF PIXELS WITHIN A SMALL WINDOW ABOUT CURRENT PIXEL
            int row = qRound(kgPoints[i].y / kgPoints[i].z);
            int col = qRound(kgPoints[i].x / kgPoints[i].z);

            // MAKE SURE THE CURRENT COORDINATE IS WITHIN THE BOUNDS OF THE IMAGE
            if (row > 0 && row < inImage.rows - 1) {
                if (col > 0 && col < inImage.cols - 1) {
                    int sum = 0;
                    for (int r = row - 1; r < row + 2; r++) {
                        for (int c = col - 1; c < col + 2; c++) {
                            sum += (inImage.at<unsigned char>(r, c) > 128);
                        }
                    }
                    // COPY THE CURRENT BIT TO THE CODE MATRIX
                    if (sum > 4) {
                        codeMatrix.at<int>(i / 4, 3 - i % 4) = 1;
                    } else {
                        codeMatrix.at<int>(i / 4, 3 - i % 4) = 0;
                    }
                }
            }
        }

        // FLIP THE CODE MATRIX LEFT-RIGHT IN CASE WE ARE
        // LOOKING AT THE TARGET FROM BEHIND WITH BACK LIGHTING
        if (flipCalTags) {
            cv::flip(codeMatrix, codeMatrix, 1);
        }

        cv::Point2f point;
        unsigned int code = decodingMatrix.dot(codeMatrix);
        if (checkBitCode(code, &point)) {
            hist[0]++;
        }

        cv::Mat matrix = codeMatrix;
        cv::transpose(matrix, matrix);
        cv::flip(matrix, matrix, 1);
        code = decodingMatrix.dot(matrix);

        if (checkBitCode(code, &point)) {
            hist[1]++;
        }

        cv::transpose(matrix, matrix);
        cv::flip(matrix, matrix, 1);
        code = decodingMatrix.dot(matrix);

        if (checkBitCode(code, &point)) {
            hist[2]++;
        }

        cv::transpose(matrix, matrix);
        cv::flip(matrix, matrix, 1);
        code = decodingMatrix.dot(matrix);

        if (checkBitCode(code, &point)) {
            hist[3]++;
        }
    }

    // DETERMINE WHICH ORIENTATION IS THE MOST FREQUENT
    int orientation = 3;
    if (hist[0] > hist[1] && hist[0] > hist[2] && hist[0] > hist[3]) {
        orientation = 0;
    } else if (hist[1] > hist[0] && hist[1] > hist[2] && hist[1] > hist[3]) {
        orientation = 1;
    } else if (hist[2] > hist[0] && hist[2] > hist[1] && hist[2] > hist[3]) {
        orientation = 2;
    }

    int validCodeCounter = 0;
    for (unsigned int n = 0; n < squares.size(); n++) {
        // DERIVE SQUARE COORDINATES TO IMAGE PIXEL COORDINATES BASED ON CURRENT SQUARE
        cv::vector<cv::Point2f> inPoints;
        for (int c = 0; c < 4; c++) {
            inPoints.push_back(squares[n][c]);
        }
        cv::Mat localTransform = cv::getPerspectiveTransform(sqPoints, inPoints);

        // MAP THE CODE BIT COORDINATES TO IMAGE PIXEL COORDINATES
        cv::Mat codeMatrix(4, 4, CV_32S);
        cv::transform(gdPoints, kgPoints, localTransform);
        for (unsigned int i = 0; i < kgPoints.size(); i++) {
            // ACCUMULATE THE SUM OF PIXELS WITHIN A SMALL WINDOW ABOUT CURRENT PIXEL
            int row = qRound(kgPoints[i].y / kgPoints[i].z);
            int col = qRound(kgPoints[i].x / kgPoints[i].z);

            // MAKE SURE THE CURRENT COORDINATE IS WITHIN THE BOUNDS OF THE IMAGE
            if (row > 0 && row < inImage.rows - 1) {
                if (col > 0 && col < inImage.cols - 1) {
                    int sum = 0;
                    for (int r = row - 1; r < row + 2; r++) {
                        for (int c = col - 1; c < col + 2; c++) {
                            sum += (inImage.at<unsigned char>(r, c) > 128);
                        }
                    }
                    // COPY THE CURRENT BIT TO THE CODE MATRIX
                    if (sum > 4) {
                        codeMatrix.at<int>(i / 4, 3 - i % 4) = 1;
                    } else {
                        codeMatrix.at<int>(i / 4, 3 - i % 4) = 0;
                    }
                }
            }
        }

        // FLIP THE CODE MATRIX LEFT-RIGHT IN CASE WE ARE
        // LOOKING AT THE TARGET FROM BEHIND WITH BACK LIGHTING
        if (flipCalTags) {
            cv::flip(codeMatrix, codeMatrix, 1);

            cv::Point2f point;
            unsigned int code = decodingMatrix.dot(codeMatrix);
            if (orientation != 0 || checkBitCode(code, &point) == false) {
                cv::Mat matrix = codeMatrix;
                cv::transpose(matrix, matrix);
                cv::flip(matrix, matrix, 1);
                code = decodingMatrix.dot(matrix);

                if (orientation != 1 || checkBitCode(code, &point) == false) {
                    cv::transpose(matrix, matrix);
                    cv::flip(matrix, matrix, 1);
                    code = decodingMatrix.dot(matrix);

                    if (orientation != 2 || checkBitCode(code, &point) == false) {
                        cv::transpose(matrix, matrix);
                        cv::flip(matrix, matrix, 1);
                        code = decodingMatrix.dot(matrix);

                        if (orientation != 3 || checkBitCode(code, &point) == false) {
                            cv::vector<cv::Point2f> square;
                            square.push_back(cv::Point2f(NAN, NAN));
                            square.push_back(cv::Point2f(NAN, NAN));
                            square.push_back(cv::Point2f(NAN, NAN));
                            square.push_back(cv::Point2f(NAN, NAN));
                            outputSquares.push_back(square);
                        } else {
                            validCodeCounter++;
                            cv::vector<cv::Point2f> square;
                            square.push_back(sqPoints[3] + point);
                            square.push_back(sqPoints[2] + point);
                            square.push_back(sqPoints[1] + point);
                            square.push_back(sqPoints[0] + point);
                            outputSquares.push_back(square);
                        }
                    } else {
                        validCodeCounter++;
                        cv::vector<cv::Point2f> square;
                        square.push_back(sqPoints[2] + point);
                        square.push_back(sqPoints[1] + point);
                        square.push_back(sqPoints[0] + point);
                        square.push_back(sqPoints[3] + point);
                        outputSquares.push_back(square);
                    }
                } else {
                    validCodeCounter++;
                    cv::vector<cv::Point2f> square;
                    square.push_back(sqPoints[1] + point);
                    square.push_back(sqPoints[0] + point);
                    square.push_back(sqPoints[3] + point);
                    square.push_back(sqPoints[2] + point);
                    outputSquares.push_back(square);
                }
            } else {
                cv::vector<cv::Point2f> square;
                square.push_back(sqPoints[0] + point);
                square.push_back(sqPoints[3] + point);
                square.push_back(sqPoints[2] + point);
                square.push_back(sqPoints[1] + point);
                outputSquares.push_back(square);
            }
        } else {
            cv::Point2f point;
            unsigned int code = decodingMatrix.dot(codeMatrix);
            if (orientation != 0 || checkBitCode(code, &point) == false) {
                cv::Mat matrix = codeMatrix;
                cv::transpose(matrix, matrix);
                cv::flip(matrix, matrix, 1);
                code = decodingMatrix.dot(matrix);

                if (orientation != 1 || checkBitCode(code, &point) == false) {
                    cv::transpose(matrix, matrix);
                    cv::flip(matrix, matrix, 1);
                    code = decodingMatrix.dot(matrix);

                    if (orientation != 2 || checkBitCode(code, &point) == false) {
                        cv::transpose(matrix, matrix);
                        cv::flip(matrix, matrix, 1);
                        code = decodingMatrix.dot(matrix);

                        if (orientation != 3 || checkBitCode(code, &point) == false) {
                            cv::vector<cv::Point2f> square;
                            square.push_back(cv::Point2f(NAN, NAN));
                            square.push_back(cv::Point2f(NAN, NAN));
                            square.push_back(cv::Point2f(NAN, NAN));
                            square.push_back(cv::Point2f(NAN, NAN));
                            outputSquares.push_back(square);
                        } else {
                            validCodeCounter++;
                            cv::vector<cv::Point2f> square;
                            square.push_back(sqPoints[0] + point);
                            square.push_back(sqPoints[1] + point);
                            square.push_back(sqPoints[2] + point);
                            square.push_back(sqPoints[3] + point);
                            outputSquares.push_back(square);
                        }
                    } else {
                        validCodeCounter++;
                        cv::vector<cv::Point2f> square;
                        square.push_back(sqPoints[3] + point);
                        square.push_back(sqPoints[0] + point);
                        square.push_back(sqPoints[1] + point);
                        square.push_back(sqPoints[2] + point);
                        outputSquares.push_back(square);
                    }
                } else {
                    validCodeCounter++;
                    cv::vector<cv::Point2f> square;
                    square.push_back(sqPoints[2] + point);
                    square.push_back(sqPoints[3] + point);
                    square.push_back(sqPoints[0] + point);
                    square.push_back(sqPoints[1] + point);
                    outputSquares.push_back(square);
                }
            } else {
                cv::vector<cv::Point2f> square;
                square.push_back(sqPoints[1] + point);
                square.push_back(sqPoints[2] + point);
                square.push_back(sqPoints[3] + point);
                square.push_back(sqPoints[0] + point);
                outputSquares.push_back(square);
            }
        }
    }
    qDebug() << "Orientations:" << hist[0] << hist[1] << hist[2] << hist[3];

    // RETURN THE MATCHING CALTAG SQUARE COORDINATES
    return (outputSquares);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
cv::vector<cv::Point2f> LAUCalTagGLObject::sortPoints(cv::vector<cv::Point> points)
{
    cv::Point2f center;
    for (unsigned int n = 0; n < points.size(); n++) {
        center += cv::Point2f((float)points[n].x, (float)points[n].y);
    }
    center = center / (float)points.size();

    QList<float> angles;
    QList<int> indices;
    for (unsigned int n = 0; n < points.size(); n++) {
        angles << atan2((float)points[n].y - center.y, (float)points[n].x - center.x);
        indices << n;
    }

    // SORT ANGLES
    for (int m = 0; m < (int)points.size() - 1; m++) {
        for (int n = m + 1; n < (int)points.size(); n++) {
            if (angles.at(m) > angles.at(n)) {
                angles.swap(m, n);
                indices.swap(m, n);
            }
        }
    }

    // RECONSTRUCT SQUARE IN CLOCKWISE ORDER
    cv::vector<cv::Point2f> output;
    for (unsigned int n = 0; n < points.size(); n++) {
        output.push_back(cv::Point2f((float)points[indices.at(n)].x, (float)points[indices.at(n)].y));
    }
    return (output);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
cv::vector<cv::vector<cv::Point2f>> LAUCalTagGLObject::organizeSquares(cv::vector<cv::vector<cv::Point2f>> squares)
{
    cv::vector<cv::vector<cv::Point2f>> outputSquares;

    for (unsigned int n = 0; n < squares.size(); n++) {
        cv::Point2f center = (squares[n][0] + squares[n][1] + squares[n][2] + squares[n][3]) / 4.0f;
        float angles[4];
        int indices[4] = { 0, 1, 2, 3 };

        angles[0] = atan2(squares[n][0].y - center.y, squares[n][0].x - center.x);
        angles[1] = atan2(squares[n][1].y - center.y, squares[n][1].x - center.x);
        angles[2] = atan2(squares[n][2].y - center.y, squares[n][2].x - center.x);
        angles[3] = atan2(squares[n][3].y - center.y, squares[n][3].x - center.x);

        // SORT ANGLES
        for (int m = 0; m < 3; m++) {
            for (int n = m + 1; n < 4; n++) {
                if (angles[m] > angles[n]) {
                    float a = angles[m];
                    angles[m] = angles[n];
                    angles[n] = a;

                    int b = indices[m];
                    indices[m] = indices[n];
                    indices[n] = b;
                }
            }
        }

        // RECONSTRUCT SQUARE IN CLOCKWISE ORDER
        cv::vector<cv::Point2f> square;
        square.push_back(squares[n][indices[0]]);
        square.push_back(squares[n][indices[1]]);
        square.push_back(squares[n][indices[2]]);
        square.push_back(squares[n][indices[3]]);
        outputSquares.push_back(square);
    }

    // PRINT OUT A REPORT ON HOW IMAGE SQUARES ARE ALIGNED AND HOW THEY GET MAPPED TO CALTAG SQUARES
    //QFile file(QString("/tmp/organizeReport.txt"));
    //if (file.open(QIODevice::WriteOnly)) {
    //    QTextStream stream(&file);
    //    for (unsigned int n = 0; n < squares.size(); n++) {
    //        for (int c = 0; c < 4; c++) {
    //            stream << QString("%1, %2, %3, %4\n").arg(squares[n][c].x).arg(squares[n][c].y).arg(outputSquares[n][c].x).arg(outputSquares[n][c].y);
    //        }
    //    }
    //    file.close();
    //}

    return (outputSquares);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
bool LAUCalTagGLObject::checkBitCode(int code, cv::Point2f *pt)
{
    // DEFINE LOOK-UP TABLE
    static const int realBitCodes[20][14] = {
        {19853,	19918,	20121,	20186,	20373,	20438,	20497,	20562,	20692,	20765,	20830,	20891,	20952,	21001},
        {18674,	18747,	18808,	18877,	18942,	18991,	19052,	19113,	19235,	19296,	19365,	19650,	19723,	19784},
        {17633,	17704,	17771,	17838,	17901,	17980,	18047,	18106,	18224,	18291,	18358,	18421,	18487,	18609},
        {16530,	16593,	16664,	16731,	16798,	16861,	16908,	16975,	17034,	17286,	17349,	17444,	17511,	17570},
        {15514,	15577,	15632,	15699,	15766,	15829,	15943,	16002,	16065,	16136,	16203,	16270,	16333,	16471},
        {14380,	14447,	14506,	14569,	14624,	14691,	14758,	14821,	14967,	15089,	15160,	15294,	15357,	15455},
        {13375,	13436,	13497,	13562,	13680,	13749,	13814,	13863,	13924,	13985,	14050,	14123,	14253,	14318},
        {12303,	12364,	12425,	12490,	12547,	12677,	12742,	12884,	12945,	13010,	13083,	13144,	13213,	13278},
        {11195,	11256,	11289,	11423,	11484,	11541,	11606,	11667,	11777,	11842,	11911,	11972,	12110,	12171},
        {10219,	10281,	10346,	10415,	10533,	10598,	10659,	10720,	10801,	10866,	10935,	10996,	11069,	11134},
        {9179,	9274,	9337,	9404,	9471,	9526,	9589,	9648,	9715,	9825,	9892,	9959,	10030,	10093},
        {8001,	8068,	8135,	8265,	8399,	8454,	8517,	8643,	8722,	8852,	8919,	8990,	9053,	9112},
        {7092,	7159,	7190,	7253,	7312,	7379,	7450,	7580,	7647,	7694,	7757,	7816,	7883,	7938},
        {6116,	6245,	6304,	6371,	6442,	6505,	6572,	6639,	6718,	6781,	6840,	6907,	6962,	7025},
        {5173,	5238,	5299,	5360,	5433,	5498,	5567,	5628,	5677,	5742,	5803,	5864,	5986,	6055},
        {4166,	4227,	4361,	4426,	4495,	4556,	4637,	4702,	4763,	4824,	4881,	4946,	5015,	5076},
        {3152,	3221,	3286,	3359,	3420,	3481,	3546,	3595,	3656,	3725,	3847,	3908,	3969,	4034},
        {2278,	2351,	2412,	2473,	2538,	2619,	2680,	2749,	2814,	2871,	2932,	2993,	3058,	3091},
        {1340,	1407,	1466,	1529,	1576,	1643,	1710,	1773,	1828,	1895,	1954,	2017,	2083,	2213},
        {197,   335,	394,	457,	603,	670,	733,	788,	855,	914,	977,	1139,	1206,	1269}
    };

    for (int i = 0; i < 20; i++) {
        for (int j = 13; j >= 0; j--) {
            if (code == realBitCodes[i][j]) {
                *pt = cv::Point2f((float)(j - 7), (float)(i - 7));
                return (true);
            } else if (code > realBitCodes[i][j]) {
                return (false);
            }
        }
    }
    return (false);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void LAUCalTagGLObject::removeOutlierPoints(cv::vector<cv::Point2f> &fmPoints, cv::vector<cv::Point2f> &toPoints)
{
    // MAKE SURE WE HAVE ENOUGH POINTS TO MAKE THIS WORTH WHILE
    if (fmPoints.size() < 20) {
        return;
    }

    // PRINT OUT A REPORT ON HOW IMAGE SQUARES ARE ALIGNED AND HOW THEY GET MAPPED TO CALTAG SQUARES
    //QFile file(QString("/tmp/outlierReport.txt"));
    //if (file.open(QIODevice::WriteOnly)) {
    //    QTextStream stream(&file);
    //    for (unsigned int n = 0; n < fmPoints.size(); n++) {
    //        stream << QString("%1, %2, %3, %4\n").arg(fmPoints[n].x).arg(fmPoints[n].y).arg(toPoints[n].x).arg(toPoints[n].y);
    //    }
    //    file.close();
    //}

    unsigned int numIterations = fmPoints.size() * 0.50;
    for (unsigned int iter = 0; iter < numIterations; iter++) {
        // GET THE BEST MAPPING BASED ON THE CURRENT SET OF POINTS
        cv::Mat transform = cv::findHomography(fmPoints, toPoints, 0);

        // CREATE A NEW SET OF TO POINTS
        cv::vector<cv::Point2f> toPts = toPoints;

        // TRANSFORM POINTS USING CURRENT TRANSFORM
        cv::perspectiveTransform(fmPoints, toPts, transform);

        // SEARCH THROUGH LIST LOOKING FOR WORST CASE POINT AND DELETE IT FROM THE LIST
        double optError = 0.0;
        unsigned int optIndex = 0;
        for (unsigned int n = 0; n < fmPoints.size(); n++) {
            cv::Point2f delta = toPoints[n] - toPts[n];
            double e = sqrt(delta.x * delta.x + delta.y * delta.y);
            if (e > optError) {
                optIndex = n;
                optError = e;
            }
        }

        // SEE IF WE ARE REALLY CLOSE AND IF SO, QUIT TRIMMING POINTS
        if (optError < 0.05) {
            break;
        }

        // DELETE THE WORST CASE POINT PAIR FROM OUR LISTS
        fmPoints.erase(fmPoints.begin() + optIndex);
        toPoints.erase(toPoints.begin() + optIndex);
        toPts.erase(toPts.begin() + optIndex);
    }

    return;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
cv::Mat LAUCalTagGLObject::findBestLinearMapping(cv::vector<cv::Point2f> fmPoints, cv::vector<cv::Point2f> toPoints)
{
    cv::Mat transformMatrix(3, 3, CV_64F);

    // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
    int N = (int)fmPoints.size();

    // ALLOCATE SPACE FOR DATA VECTORS
    cv::vector<double> cVec(N);
    cv::vector<double> rVec(N);
    cv::vector<double> xVec(N);
    cv::vector<double> yVec(N);

    // COPY DATA FROM CLUSTER LIST INTO DATA VECTORS
    for (int n = 0; n < N; n++) {
        cVec[n] = fmPoints[n].x;
        rVec[n] = fmPoints[n].y;

        xVec[n] = toPoints[n].x;
        yVec[n] = toPoints[n].y;
    }

    // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
    cv::Mat A(N, 3, CV_64F);
    cv::Mat B(N, 2, CV_64F);

    for (int r = 0; r < N; r++) {
        // POPULATE THE ODD NUMBERED ROWS
        A.at<double>(r, 0) = cVec[r];
        A.at<double>(r, 1) = rVec[r];
        A.at<double>(r, 2) = 1.0;

        B.at<double>(r, 0) = xVec[r];
        B.at<double>(r, 1) = yVec[r];
    }
    cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

    transformMatrix.at<double>(0, 0) = sVec.at<double>(0, 0);
    transformMatrix.at<double>(0, 1) = sVec.at<double>(1, 0);
    transformMatrix.at<double>(0, 2) = sVec.at<double>(2, 0);
    transformMatrix.at<double>(1, 0) = sVec.at<double>(0, 1);
    transformMatrix.at<double>(1, 1) = sVec.at<double>(1, 1);
    transformMatrix.at<double>(1, 2) = sVec.at<double>(2, 1);
    transformMatrix.at<double>(2, 0) = 0.0;
    transformMatrix.at<double>(2, 1) = 0.0;
    transformMatrix.at<double>(2, 2) = 1.0;

    return (transformMatrix);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
cv::Mat LAUCalTagGLObject::findBestQuadraticMapping(cv::vector<cv::Point2f> fmPoints, cv::vector<cv::Point2f> toPoints, int width, int height, int order)
{
    cv::Mat lVec(30, 1, CV_64F);
    lVec.setTo(0.0);

    int numPoints = (int)fmPoints.size();

    // ALLOCATE SPACE FOR DATA VECTORS
    cv::vector<double> rVec(numPoints);
    cv::vector<double> cVec(numPoints);
    cv::vector<double> xVec(numPoints);
    cv::vector<double> yVec(numPoints);

    // COPY DATA FROM CLUSTER LIST INTO DATA VECTORS
    for (int n = 0; n < numPoints; n++) {
        cVec[n] = (fmPoints[n].x - (width / 2)) / 50.0;
        rVec[n] = (fmPoints[n].y - (height / 2)) / 50.0;
        xVec[n] = toPoints[n].x;
        yVec[n] = toPoints[n].y;
    }

    if (order == 4) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 15) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 30, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints,  1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0)  = cVec[r] * cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 1)  = cVec[r] * cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 2)  = cVec[r] * cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 3)  = cVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 4)  = rVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 5)  = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 6)  = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 7)  = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 8)  = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 9)  = cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 10) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 11) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 12) = cVec[r];
                A.at<double>(2 * r + 0, 13) = rVec[r];
                A.at<double>(2 * r + 0, 14) = 1.0;

                A.at<double>(2 * r + 1, 15) = cVec[r] * cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 16) = cVec[r] * cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 17) = cVec[r] * cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 18) = cVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 19) = rVec[r] * rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 20) = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 21) = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 22) = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 23) = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 24) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 25) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 26) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 27) = cVec[r];
                A.at<double>(2 * r + 1, 28) = rVec[r];
                A.at<double>(2 * r + 1, 29) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            lVec = (A.t() * A).inv() * A.t() * B;
        }
    } else if (order == 3) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 10) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 20, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints,  1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0) = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 1) = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 2) = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 3) = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 4) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 5) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 6) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 7) = cVec[r];
                A.at<double>(2 * r + 0, 8) = rVec[r];
                A.at<double>(2 * r + 0, 9) = 1.0;

                A.at<double>(2 * r + 1, 10) = cVec[r] * cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 11) = cVec[r] * cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 12) = cVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 13) = rVec[r] * rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 14) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 15) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 16) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 17) = cVec[r];
                A.at<double>(2 * r + 1, 18) = rVec[r];
                A.at<double>(2 * r + 1, 19) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

            // COPY SVECTOR OVER TO LVECTOR
            for (int n = 0; n < 10; n++) {
                lVec.at<double>(n + 5) = sVec.at<double>(n + 0);
                lVec.at<double>(n + 20) = sVec.at<double>(n + 10);
            }
        }
    } else if (order == 2) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 6) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 12, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints,  1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0) = cVec[r] * cVec[r];
                A.at<double>(2 * r + 0, 1) = cVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 2) = rVec[r] * rVec[r];
                A.at<double>(2 * r + 0, 3) = cVec[r];
                A.at<double>(2 * r + 0, 4) = rVec[r];
                A.at<double>(2 * r + 0, 5) = 1.0;

                A.at<double>(2 * r + 1, 6)  = cVec[r] * cVec[r];
                A.at<double>(2 * r + 1, 7)  = cVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 8)  = rVec[r] * rVec[r];
                A.at<double>(2 * r + 1, 9)  = cVec[r];
                A.at<double>(2 * r + 1, 10) = rVec[r];
                A.at<double>(2 * r + 1, 11) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

            // COPY SVECTOR OVER TO LVECTOR
            for (int n = 0; n < 6; n++) {
                lVec.at<double>(n + 9) = sVec.at<double>(n + 0);
                lVec.at<double>(n + 24) = sVec.at<double>(n + 6);
            }
        }
    } else if (order == 1) {
        // MAKE SURE WE FOUND ENOUGH CLUSTERS TO DO A DECENT INTERPOLATION
        if (fmPoints.size() >= 3) {
            // CREATE MATRIX TO HOLD THE 4TH ORDER TRANSFORM
            cv::Mat A(2 * numPoints, 6, CV_64F);
            A.setTo(0.0);
            cv::Mat B(2 * numPoints, 1, CV_64F);

            for (int r = 0; r < numPoints; r++) {
                // POPULATE THE ODD NUMBERED ROWS
                A.at<double>(2 * r + 0, 0) = cVec[r];
                A.at<double>(2 * r + 0, 1) = rVec[r];
                A.at<double>(2 * r + 0, 2) = 1.0;

                A.at<double>(2 * r + 1, 3) = cVec[r];
                A.at<double>(2 * r + 1, 4) = rVec[r];
                A.at<double>(2 * r + 1, 5) = 1.0;

                B.at<double>(2 * r + 0) = xVec[r];
                B.at<double>(2 * r + 1) = yVec[r];
            }
            cv::Mat sVec = (A.t() * A).inv() * A.t() * B;

            // COPY SVECTOR OVER TO LVECTOR
            for (int n = 0; n < 3; n++) {
                lVec.at<double>(n + 12) = sVec.at<double>(n + 0);
                lVec.at<double>(n + 27) = sVec.at<double>(n + 3);
            }
        }
    }
    return (lVec);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
float LAUCalTagGLObject::length(cv::Point2f point)
{
    return (sqrt(point.x * point.x + point.y * point.y));
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
float LAUCalTagGLObject::angle(cv::Point2f point)
{
    return (atan2(point.y, point.x));
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
LAUMemoryObject LAUCalTagGLObject::grabImage()
{
    LAUMemoryObject object;
    if (frameBufferObjectB) {
        object = LAUMemoryObject(frameBufferObjectB->width(), frameBufferObjectB->height(), 3, sizeof(float));
        glBindTexture(GL_TEXTURE_2D, frameBufferObjectB->texture());
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, object.constPointer());
    }
    return (object);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void LAUCalTagGLObject::paintGL()
{
    if (frameBufferObjectB) {
        // DISPLAY THE LAST FBO IN OUR LIST
        if (programK.bind()) {
            if (quadVertexBuffer.bind()) {
                if (quadIndexBuffer.bind()) {
                    // SET THE ACTIVE TEXTURE ON THE GPU
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, frameBufferObjectB->texture());
                    programK.setUniformValue("qt_texture", 0);

                    // TELL OPENGL PROGRAMMABLE PIPELINE HOW TO LOCATE VERTEX POSITION DATA
                    programK.setAttributeBuffer("qt_vertex", GL_FLOAT, 0, 4, 4 * sizeof(float));
                    programK.enableAttributeArray("qt_vertex");

                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    quadIndexBuffer.release();
                }
                quadVertexBuffer.release();
            }
            programK.release();
        }
    }
}
