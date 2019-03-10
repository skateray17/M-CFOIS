const ruAlphabet = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя';
const encryptKey = 'ГЛФЫЗШБЖХЁПВЧНКЪЭДЬРЕТСАМЮЦЩЯУИОЙ';
const encryptMessage = 'конфиденциальность';
const decryptKey = 'ЛБВ';
const decryptMessage = 'ЛУФШФЩЛ';
const newDecryptMessage = 'ЛИКШЙПЛ';

const encrypt5 = (alphabet, key, message) => {
    const keyMap = {};
    [...alphabet].forEach((e, i) => keyMap[e] = key.charAt(i));
    return [...message].map(e => keyMap[e]).join('');
}

const decrypt5 = (alphabet, key, message) => {
  const UCAlphabet = alphabet.split('');
  return [...message]
  .map((e, i) => UCAlphabet[(
    UCAlphabet.length + UCAlphabet.indexOf(e) - UCAlphabet.indexOf(key[i % key.length])
    ) % UCAlphabet.length])
    .join('');
  }
  
console.log(`result of encrypting ${encryptMessage} with key ${encryptKey} is ${encrypt5(ruAlphabet, encryptKey, encryptMessage)}`);

console.log(`Probably there was wrong key or it was encrypted via shift cipher: ${decrypt5(ruAlphabet.toUpperCase(), decryptKey, decryptMessage)}`);
console.log(`If we take just first symbol of the key: ${decrypt5(ruAlphabet.toUpperCase(), decryptKey[0], decryptMessage)}`);

console.log(`There was lab update, that fixed mistake: ${decrypt5(ruAlphabet.toUpperCase(), decryptKey, newDecryptMessage)}`);
