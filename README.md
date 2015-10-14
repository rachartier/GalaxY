# GalaxY

GalaxY est un jeu en console d'aventure et d'exploration spatiale. Vous traversez les galaxies à bord de votre vaisseau en passant par différents systèmes solaires générés aléatoirement. Durant le trajet, vous pourrez fouiller et découvrir des trésors sur les planètes rencontrées, et commercer avec ces dernières pour récupérer des marchandises de base (nourriture, eau, fuel) mais aussi pour recruter du personnel sur votre vaisseau. En plus de leur commerce, les planètes possèdent leur propre régime politique allant de la simple république à la monarchie en passant par la dictature. Un décodeur pourra alors vous être utile (en cas de langue inconnu par votre équipage), vous pourrez le débloquer dans un système de drop aléatoire vous permettant de récupérer aussi des armes, des armures, de l'argent, du fuel, etc. Au fur et à mesure que l'équipage s'agrandit, il faudra adapter votre vaisseau en le personnalisant et en l'améliorant (taille, capacité de transport, réservoir, armure, dégât, etc). Chacun des membres de votre équipage occupera un poste bien précis, vous donnant alors un bonus utile lors de batailles par exemple pour vous défendre (ou attaquer !).

# Aide

## Commande

Si vous ne vous rappelez plus d'une commande ou de comment l'utiliser, tapez `?` pour faire apparaître l'aide, ou tapez la commande sans argument pour avoir les informations sur cette commande précise.

| Commande           | Abréviation | Description                                  |
| --------           | :---------- | :----------                                  |
| `liste`            | `ls`        | liste toutes les planètes du système solaire |
| `aller [argument]` | `al`        | permet de se déplacer de planète en planète  |
| `aller suiv`       | `al s`      | se déplace sur la planète suivante           |
| `aller prec`       | `al p`      | se déplace sur la planète précédente         |
| `fouiller`         | `f`         | fouille la planète actuelle                  |
| `info [argument]`  |             | donne des informations                       |
| `info`             |             | informations de la planète actuelle          |
| `info vaisseau`    | `info v`    | informations de votre vaisseau               |
| `info equipage`    | `info e`    | informations sur votre équipage              |
| `quitte`           | `q`         | quitte la partie en cours                    |

(A venir)

- `commerce` (`c`) : donne accès au menu de commerce de la planète actuelle.
- `bataille` (`b`) : votre vaisseau entre dans le mode de bataille.

# TODO

(Vaisseau)
- Possibilité de personnaliser/améliorer son vaisseau (taille, capacité, réservoir, puissance, armure)
- Équipage avec poste + bonus de poste

(Joueur)
- Nombre limite de déplacement en fonction du fuel
- Charge maximum du vaisseau
- Arme/armure
- Système d'argent
- Nourriture/eau (pour l'équipage)
- Système de combat : attaque et défense
- Système de drop/item
- Système de quête

(Planète)
- Commerce planète
- Régime politique planète
- Langue inconnue

# Licence

Ce projet est sous licence [MIT](http://opensource.org/licenses/mit-license.php).
