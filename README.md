| Opcode | Description                                                                          | done |
|--------|--------------------------------------------------------------------------------------|------|
| 00E0   | CLS : Effacer l’écran                                                                | ✅    |
| 00EE   | RET : Retour d’une sous-routine                                                      | ✅    |
| 1nnn   | JP addr : Aller à l’adresse nnn                                                      | ✅    |
| 2nnn   | CALL addr : Appeler la sous-routine à l’adresse nnn                                  | ✅    |
| 3xkk   | SE Vx, byte : Saute l’instruction suivante si Vx == kk                               | ✅    |
| 4xkk   | SNE Vx, byte : Saute si Vx != kk                                                     | ✅    |
| 5xy0   | SE Vx, Vy : Saute si Vx == Vy                                                        | ✅    |
| 6xkk   | LD Vx, byte : Met la valeur kk dans Vx                                               | ✅    |
| 7xkk   | ADD Vx, byte : Ajoute kk à Vx                                                        | ✅    |
| 8xy0   | LD Vx, Vy : Copie Vy dans Vx                                                         | ✅    |
| 8xy1   | OR Vx, Vy : Vx = Vx OR Vy                                                            | ✅    |
| 8xy2   | AND Vx, Vy : Vx = Vx AND Vy                                                          | ✅    |
| 8xy3   | XOR Vx, Vy : Vx = Vx XOR Vy                                                          | ✅    |
| 8xy4   | ADD Vx, Vy : Ajoute Vy à Vx, VF = retenue                                            | ✅    |
| 8xy5   | SUB Vx, Vy : Vx = Vx - Vy, VF = NOT retenue                                          | ✅    |
| 8xy6   | SHR Vx {, Vy} : Décale Vx à droite d’un bit, VF = bit de poids faible avant décalage | ✅    |
| 8xy7   | SUBN Vx, Vy : Vx = Vy - Vx, VF = NOT retenue                                         | ✅    |
| 8xyE   | SHL Vx {, Vy} : Décale Vx à gauche d’un bit, VF = bit de poids fort avant décalage   | ✅    |
| 9xy0   | SNE Vx, Vy : Saute si Vx != Vy                                                       | ✅    |
| Annn   | LD I, addr : Charge I avec l’adresse nnn                                             | ✅    |
| Bnnn   | JP V0, addr : Saute à l’adresse nnn + V0                                             | ✅    |
| Cxkk   | RND Vx, byte : Vx = nombre aléatoire AND kk                                          | ✅    |
| Dxyn   | DRW Vx, Vy, nibble : Dessine un sprite de hauteur nibble à (Vx, Vy)                  | ✅    |
| Ex9E   | SKP Vx : Saute si la touche Vx est pressée                                           | ✅    |
| ExA1   | SKNP Vx : Saute si la touche Vx n’est pas pressée                                    | ✅    |
| Fx07   | LD Vx, DT : Vx = délai timer                                                         | ✅    |
| Fx0A   | LD Vx, K : Attend une touche et stocke la valeur dans Vx                             | ✅    |
| Fx15   | LD DT, Vx : Définit le délai timer à Vx                                              | ✅    |
| Fx18   | LD ST, Vx : Définit le timer son à Vx                                                | ✅    |
| Fx1E   | ADD I, Vx : I = I + Vx                                                               | ✅    |
| Fx29   | LD F, Vx : Charge I avec l’adresse du sprite pour le chiffre Vx                      | ✅    |
| Fx33   | LD B, Vx : Stocke la représentation BCD de Vx à I, I+1, I+2                          | ✅    |
| Fx55   | LD \[I], Vx : Stocke V0 à Vx en mémoire à partir de l’adresse I                      | ✅    |
| Fx65   | LD Vx, \[I] : Charge V0 à Vx depuis la mémoire à partir de I                         | ✅    |

Notes importantes :
n, x, y, kk, nnn représentent respectivement un nibble (4 bits), un registre (0-F), un registre (0-F), un octet (8 bits)
et une adresse 12 bits.

La plupart des instructions sont codées sur 2 octets (16 bits).

Les instructions 8xy* sont des instructions arithmétiques/logiques diverses.

Le registre VF est souvent utilisé comme flag pour la retenue ou le carry.

