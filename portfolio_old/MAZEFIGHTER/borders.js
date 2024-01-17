import * as ROT from "./rotjs/lib/index.js";

function createMap(width, height) {
    let map = {
        width, height,
        tiles: new Map(),
        key(x, y) {return `${x},${y}`;},
        get(x, y) {return this.tiles.get(this.key(x, y));},
        set(x, y, value) {this.tiles.set(this.key(x, y), value);},
    };
    
    let maze = new ROT.Map.EllerMaze(width, height);
    maze.create((x, y, contents) => map.set(x, y, contents));
    return map;
}

function draw(display, map) {
    display.clear();
    for (let y = 0; y < map.height; y++) {
        for (let x = 0; x < map.width; x++) {
            if (map.get(x, y)) {
                display.draw(x, y, '⨉', "hsl(60, 10%, 40%)", "gray");
            } else {
                display.draw(x, y, '·', "hsl(60, 50%, 50%)", "black");
            }
        }
    }
}

export function createBorder(width, height, id) {
    let display = new ROT.Display({width: width, height: height,
        forceSquareRatio:true, fontSize: 4});
    document.getElementById(id).appendChild(display.getContainer());
    let map = createMap(width, height);
    draw(display, map);
}

