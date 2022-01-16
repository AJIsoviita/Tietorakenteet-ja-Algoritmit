Tietorakenteet ja algoritmit | COMP.CS.300
Antti-Jussi Isoviita | H283435 | antti-jussi.isoviita@tuni.fi

Tietorakenteet
struct Way {std::vector<Coord> route; unsigned int length; bool on_stack};
	Rakenne risteyksien välisten väylien tallentamiseksi
	route: mahdollisten reittikoordinaattien tallentamiseksi
	length: lyhyimmän reitin etsimiseksi
	on_stack: kertoo apufunktiolle onko reitti lisätty stackkiin

std::vector<WayID> Way_IDs;
	Rakenne mahdollisten väylien ID:eiden tallentamiseksi
	Syy: Mahdollista lisätä ja poistaa alkioita nopeasti

std::unordered_map<WayID, Way> Ways;
	Rakenne väylien tallentamiseksi
	WayID: identifioi väylät niille annetulla nimellä
	Way: antaa tarvittavat tiedot väylästä
	Syy: Järjestystä ei tarvita, find toimii nopeammin unordered_map rakenteella kuin map rakenteella

std::unordered_map<Coord, bool, CoordHash> Waypoints;
	Rakenne risteysten tallentamiseksi
	Coord: Risteyksen sijainti
	bool: onko risteyksessä oltu
	Syy: Järjestystä ei tarvita, find toimii nopeammin unordered_map rakenteella kuin map rakenteella

std::unordered_map<Coord, std::vector<WayID>, CoordHash> Crossroads;
	Rakenne risteyksistä lähtevien mahdollisten väylien tallentamiseksi
	Coord: risteyksen sijainti
	std::vector<WayID>: risteyksestä voi lähteä useita eri väyliä
	Syy: Järjestystä ei tarvita, find toimii nopeammin unordered_map rakenteella kuin map rakenteella

Apufunktiot
std::vector<std::tuple<Coord, WayID, Distance> > Dijkstra (Coord, Coord);
	Funktio lyhyimmän reitin löytämiseksi, toteutettu pseudokoodin perusteella.
	Ottaa parametreinä alku- ja loppukoordinaatit, palauttaa reitin alusta loppuun halutussa muodossa.
	Tehokkuus:  O(n log n), Dijkstran implementaatio, excelillä laskettu sijoittuvan hieman alle n log n

std::vector<WayID> AddEdge (Coord);
	Apufunktio Dijkstralle, tarkistaa onko parametrina annetussa risteyksessä käyty.
	Tehokkuus:  O(1): Find funktio unordered_map rakenteelle

