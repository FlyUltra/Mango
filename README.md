# Mango

## Popis projektu

**Mango** je experimentální síťový a datový engine napsaný v C++, jehož cílem je návrh vysoce výkonné komunikace klient–server s minimálním overheadem. Projekt se zaměřuje na binární protokol, efektivní serializaci dat a řízení síťového provozu při vysoké zátěži.

Dlouhodobým cílem projektu je vytvořit základ, který bude v určitých scénářích (low-latency messaging, real-time systémy, řízený přenos dat) **výkonnější než Redis používající textový protokol RESP**, zejména díky eliminaci textového parsování a snížení režie komunikace.

Projekt je navržen jako studijní a experimentální, nikoliv jako plnohodnotná náhrada existujících databázových systémů.

---

## Aktuální stav projektu

### MUCP – Mango Unified Communication Protocol

* vlastní binární síťový protokol nad TCP
* pevná hlavička + binární payload
* persistentní spojení bez opakovaného handshaku
* funkční client–server komunikace
* end-to-end přenos dat otestován
* navrženo s důrazem na nízkou latenci a predikovatelné chování

MUCP slouží jako transportní vrstva, nad kterou je možné stavět aplikační protokol bez nutnosti textového parsování.

---

### MSON – Mango Serialized Object Notation

* vlastní strukturovaný serializační formát (alternativa k JSON)
* převod textové reprezentace na objekt
* binární serializace objektů
* kompaktní a deterministický binární zápis
* podpora základních typů: string, integer, boolean, object

MSON je používán jako aplikační payload přenášený protokolem MUCP.

---

### Integrace MUCP a MSON

* MSON objekty jsou serializovány do binární podoby
* binární data jsou přenášena přes MUCP
* server data správně přijímá a zpracovává
* celý datový tok je funkční:

```
Object → MSON → MUCP → Server
```

---

## Směřování projektu (plánovaný vývoj)

### In-memory datová vrstva

Plánováno je rozšíření projektu o jednoduchý in-memory key-value store:

* podpora příkazů `SET`, `GET`, `UPDATE`, `DEL`
* namespace / „public listiny“
* automatické (lazy) vytvoření listiny při prvním přístupu
* ukládání hodnot ve formátu MSON

Tato vrstva bude přímo integrována nad MUCP bez externích závislostí.

---

### Batchování a vysoká zátěž

Jedním z hlavních cílů projektu je optimalizace chování při vysokém provozu:

* batchování více zpráv do jednoho síťového zápisu
* snížení počtu `send()` operací
* efektivní zpracování overload traffic
* testování chování při vysokém počtu requestů za sekundu

Cílem je dosáhnout vyšší propustnosti než u textových protokolů v binárně orientovaných scénářích.

---

### Řízení provozu a stabilita

Do budoucna je plánováno:

* řízení toku dat (backpressure)
* detekce přetížení serveru
* řízené zpomalování nebo odmítání klientů při overloadu
* oddělení síťové a aplikační logiky

---

## Cíl projektu

Cílem projektu:

* návrh vlastního binárního protokolu
* implementace efektivní serializace dat
* pochopení síťové komunikace na nízké úrovni
* experimentování s výkonem a škálováním

Projekt slouží jako technický základ pro další rozšiřování a výzkum.

---

## FAQ

### Proč nepoužít hotové řešení jako Redis?

Redis je univerzální nástroj s bohatou funkcionalitou. Mango má odlišný cíl = minimalizovat overhead komunikace a umožnit optimalizace, které nejsou v univerzálním řešení možné.

---

### V čem má Mango potenciál být rychlejší než Redis?

Redis používá textový protokol RESP, který vyžaduje parsování řetězců. Mango používá binární protokol a binární serializaci, což snižuje množství zpracování na obou stranách při jednoduchých operacích.

---

### Znamená to, že Mango Redis nahradí?

Projekt Mango není zamýšlen jako náhrada Redis. Redis zůstává vhodnější pro obecné použití.

---

### Proč TCP a ne UDP?

TCP poskytuje spolehlivost, zachování pořadí zpráv a řízení toku, což zjednodušuje návrh aplikační vrstvy. Projekt se zaměřuje na optimalizaci nad TCP, nikoliv na řešení ztrát paketů.

---

### Jak Mango řeší vysokou zátěž?

Aktuálně je projekt ve fázi návrhu. Plánováno je batchování, omezení toku dat, detekce přetížení a řízené zpomalování klientů.

---

### Jaké typy dat Mango podporuje?

Projekt používá formát MSON, který aktuálně podporuje string, integer, boolean a objekt. Formát je navržen jako rozšiřitelný.

---

### Jak je řešena přenositelnost?

Projekt je napsán v čistém C++ bez externích závislostí, používá CMake a je navržen jako cross-platform (Windows / POSIX).

---

### Jaký je další krok ve vývoji?

Nejbližší kroky jsou implementace in-memory store, request-response komunikace a systematické měření výkonu.


---

Použité zdroje:

https://cs.wikipedia.org/wiki/Transmission_Control_Protocol
https://en.wikipedia.org/wiki/Redis
https://medium.com/@kristian15994/custom-tcp-protocol-in-go-part-1-c7ea48ae7a9e
https://medium.com/@naseefcse/ip-tcp-programming-for-beginners-using-c-5bafb3788001