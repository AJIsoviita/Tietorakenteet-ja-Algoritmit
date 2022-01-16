Tietorakenteet ja algoritmit | COMP.CS.300
Antti-Jussi Isoviita | H283435 | antti-jussi.isoviita@tuni.fi

Tietorakenteet
struct Place {Name name; PlaceType type; Coord coordinates;};
	Paikoista piti tallentaa nimi, tyyppi ja koordinaatit. Niiden tallentaminen on loogisinta structissa,
	koska ne voidaan liittää osaksi toista tietorakennetta hyödyntämällä yksilöivää ID:tä.

struct Region {Name name; std::vector<Coord> shape;};
	Alueista piti tallentaa nimi ja monta koordinaattia. Monen koordinaatin tallentaminen
	on hyödyllistä vektorissa, koska ei tiedetä montako koordinaattia alueella on. Myöskin alkioiden 
	läpikäynti on helppoa ja nopeaa.
	Nimi - koordinaatti yhdistelmän tallentaminen on loogisinta structissa, koska ne voidaan
	liittää osaksi toista tietorakennetta hyödyntämällä yksilöivää ID:tä.

std::vector<long int> Place_IDs;
std::vector<long int> Region_IDs;
	Paikkojen ja alueiden yksiloivät ID:t ovat tallennettuja vektoreihin, koska alkioiden indeksien 
	käsittely tapahtuu tehokkuudella O(1) ja etsintä O(n). Datastructures.cc puolella käytettiin myös
	muita vektoreita, mutta samoista syistä.

std::unordered_map<AreaID, AreaID> Relations;
std::unordered_map <PlaceID, Place> Places;
std::unordered_map <AreaID, Region> Regions;
	Kokonaistietorakenteiksi valittiin unordered_map, koska alkioita ei tarvinnut saada ID-järjestyksessä
	ja se antaa find algoritmille tehokkuuden O(1). Unordered_map mahdollisti myös structien yhdistämisen
	tietokannaksi ID:n perusteella.