#define NUM_RESISTORS_TYPES 88
#define NUM_TOLARANCE_TYPES 5


// Paar type resistoren 
// TODO: uitbreiden!
long resistor_types_tenth[NUM_RESISTORS_TYPES] = {
  10, 22, 47, 56, 75, 82, 100, 120, 150, 180,                 // R range #0-9
  220, 270, 330, 390, 470, 520, 560, 680, 750, 820,           // R range #10-19
  890, 1000, 1200, 1300, 1500, 1800, 2200, 2700, 3300, 3600,  // R range #20-29
  3900, 4700, 5100, 5600, 6800, 8200,                         // R range #30-35
  10000, 13000, 15000, 18000, 20000, 22000, 27000, 30000,     // K Range #36-43
  33000, 36000, 39000, 47000, 56000, 68000, 75000, 82000,     // K Range #44-51
  100000, 120000, 150000, 180000, 220000, 270000, 330000,     // 10K Range #52-58
  390000, 470000, 560000, 600000, 680000, 750000, 820000,     // 10K Range #59-65
  1000000, 1200000, 1300000, 1500000, 1800000, 2200000,       // 100K Range #66-71
  2700000, 3300000, 3900000, 4700000, 5600000, 6800000,       // 100K Range 72-77
  7200000, 8200000,                                           // 100K Range 78-79
  10000000, 15000000, 20000000, 27000000, 33000000,           // M range 80-84
  47000000, 56000000,                                         // M range 85-86
  100000000                                                   // 10M range 87-
};



float tolerance_types[NUM_TOLARANCE_TYPES] = {
  0.01,     // Afwijking. 1% bruin band
  0.02,     // Afwijking. 2% rood band
  0.025,    // Afwijking. 2.5% blauwe band
  0.05,     // Afwijking. Standaard 5% gouden band
  0.1       // Afwijking. 10% silveren band
};
