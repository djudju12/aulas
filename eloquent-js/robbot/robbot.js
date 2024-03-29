const roads = [
   "Alice's House-Bob's House", "Alice's House-Cabin",
   "Alice's House-Post Office", "Bob's House-Town Hall",
   "Daria's House-Ernie's House", "Daria's House-Town Hall",
   "Ernie's House-Grete's House", "Grete's House-Farm",
   "Grete's House-Shop", "Marketplace-Farm",
   "Marketplace-Post Office", "Marketplace-Shop",
   "Marketplace-Town Hall", "Shop-Town Hall"
];

function build_graph(edges) {
   let graph = new Map();
   function add_edged(from, to) {
      if (graph[from] == null) {
         graph[from] = [to];
      } else {
         graph[from].push(to);
      }
   }

   for (let [from, to] of edges.map(r => r.split("-"))) {
      add_edged(from, to);
      add_edged(to, from);
   }

   return graph;
}

road_graph = build_graph(roads);

class VillageState {
   constructor(place, parcels) {
      this.place = place;
      this.parcels = parcels;
   }

   move(destination) {
      if (!road_graph[this.place].includes(destination)) {
         return this;
      } else {
         let parcels = this.parcels.map(p => {
            if (p.place != this.place) return p;
            return {place: destination, address: p.address};
         }).filter(p => p.place != p.address);
         return new VillageState(destination, parcels);
      }
   }
}

village = new VillageState();

console.log(build_graph(roads));