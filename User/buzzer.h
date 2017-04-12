#ifndef BUZZER_H
#define BUZZER_H

// ===== Init ===== //
void buzzer_init();
void T0_Init();

/* Fonction de calcul de la fréquence en fonction de l'octave */
int freqNote(int fb,int oc);

#endif