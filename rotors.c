r1++;
for (int i = 0; i < r1; i ++){
    char tmp = rotor1[0];
    int len = strlen(rotor1);
    for (int j = 0; i < (len - 1); i++){
        rotor[j] = rotor[j + 1];
    }
    rotor1[len - 1] = tmp;
}

/* TODO:
 * initial settings
 *  if r1 != 0
 *      for loop of length r1
 *          shift chars of r1
 *  if r2 != 0
 *      for loop of length r2
 *          shift chars of r2
 *  if r3 != 0
 *      for loop of length r3
 *          shift chars of r3
 *
 * before each encoding:
 *  r1++
 *  for loop of length r1
 *      shift chars of r1
 *  if r1 == 26:
 *      r2++
 *      r1 = 0
 *      for loop of length r2
 *          shift chars of r2
 *  if r2 == 26:
 *      r3 = (r3 + 1) % 26
 *      r2 = 0
 *      for loop of length r3
 *          shift chars of r3
