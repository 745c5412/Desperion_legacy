#Disclaimer - Legacy code
Ceci est une ancienne version de mon �mulateur en C++ Desperion, qui contient entre autres le serveur de jeu. Elle �tait jusqu�ici herberg�e sur un repo priv� Assembla. Suite aux nombreuses demandes, je la mets en ligne publiquement sur github.

#Desperion

Desperion est un �mulateur pour le MMORPG Dofus 2.0 �crit en C++, actuellement compatible avec la version:
2.5.5.55487.2

LՎquipe de d�veloppement de Desperion est compos�e de:
- LittleScaraby
- Nekkro, d�veloppeur

LՎmulateur utilise la collection de biblioth�ques boost (notamment boost.asio), l'API C MySQL pour les interactions avec la base de donn�es, ainsi que la biblioth�que CryptoPP pour le cryptage RSA et MD5.
De par leur quantit�, les fichiers utilis�s par lՎmulateur relatifs � boost ne sont pas inclus dans le r�pertoire "Libs". Il vous faudra t�l�charger boost sur le site officiel pour pouvoir compiler Desperion:
<http://www.boost.org/>

Les tables contenant les fichiers de cache du client (.D2O) sont mises � jour r�guli�rement pour assurer une parfaite concordance de contenu avec le serveur officiel.

Contact:
Mail -> <martin.alex32@hotmail.fr>
Skype -> alexxxxxx195