#Disclaimer - Legacy code
Ceci est une ancienne version de mon émulateur en C++ Desperion, qui contient entre autres le serveur de jeu. Elle était jusqu’ici herbergée sur un repo privé Assembla. Suite aux nombreuses demandes, je la mets en ligne publiquement sur github.

#Desperion

Desperion est un émulateur pour le MMORPG Dofus 2.0 écrit en C++, actuellement compatible avec la version:
2.5.5.55487.2

L’équipe de développement de Desperion est composée de:
- LittleScaraby
- Nekkro, développeur

L’émulateur utilise la collection de bibliothèques boost (notamment boost.asio), l'API C MySQL pour les interactions avec la base de donnÈes, ainsi que la bibliothèque CryptoPP pour le cryptage RSA et MD5.
De par leur quantité, les fichiers utilisés par l’émulateur relatifs à boost ne sont pas inclus dans le répertoire "Libs". Il vous faudra télécharger boost sur le site officiel pour pouvoir compiler Desperion:
<http://www.boost.org/>

Les tables contenant les fichiers de cache du client (.D2O) sont mises à jour régulièrement pour assurer une parfaite concordance de contenu avec le serveur officiel.

Contact:
Mail -> <martin.alex32@hotmail.fr>
Skype -> alexxxxxx195