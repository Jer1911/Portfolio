import * as ROT from "./rotjs/lib/index.js";
import * as border from "./borders.js";

/******************************************************************************
* FUNCTION DEFINITIONS:                                                       *
******************************************************************************/

// BORDERS: -------------------------------------------------------------------
function drawGameBorders() {
    try {
        border.createBorder(245, 10, 'top');
        border.createBorder(10, 200, 'left');
        border.createBorder(10, 200, 'right');
        border.createBorder(245, 10, 'bottom');
    }
    catch(err) {
        console.log(err);
    }
}

// HEALTHBAR: -----------------------------------------------------------------
/**Set the values in the healthbar. */
function drawHealthbar() {
    healthbar.min = 0.0;
    healthbar.max = ENTITY_PROPERTIES.player.baseHealth;
    healthbar.value = player.health;
    healthbar.low = ENTITY_PROPERTIES.player.baseHealth * 0.33;
    healthbar.high = ENTITY_PROPERTIES.player.baseHealth * 0.66;
    healthbar.optimum = ENTITY_PROPERTIES.player.baseHealth * 1.0;
}

// PAUSE and INVENTORY MENUs: -------------------------------------------------
/**Set the menu to visible and the paused flag to true. */
function pauseGame() {
    paused = true;
    menu.style.visibility = 'visible';
}

/**Draw the basic pause menu. */
function drawMenu() {
    pauseGame();
    let header = `<div>Game Paused</div><br>`;
    let mazeInfoString = ``;
    if(roomCountInt > 0) {
        mazeInfoString += roomCountInt + " rooms of size " + roomSizeInt;
    }
    else if(holeCountInt > 0) {
        mazeInfoString += holeCountInt + " holes dug";
    }
    let player_info = `
        <div style="display: grid; grid-template-columns: 300px 300px 300px;">
            <div>
                <h4>Player Info:</h4>
                <p>Player Level: ${playerLevel}</p>
                <p>Health: ${player.health}</p>
                <p>Attack Power: ${player.power}</p>
                <p>Defense: ${player.defense}</p>
                <p>Gold: ${playerGold}</p>
            </div>
            <div>
                <h4>Maze Info:</h4>
                <p>Dungeon Level: ${dungeonLevel}</p>
                <p>Maze Type: ${mazeTypeString}</p>
                <p>${mazeInfoString}</p>
                <p>${itemCountInt} items</p>
                <p>${monsterCountInt} monsters</p>
            </div>
            <div>
                <h4>Helpful Info:</h4>
                <p>Press 'i' to access your inventory</p>
                <p>Press 'ESC' to resume game</p>
            </div>
        </div>
    `;
    menu.innerHTML = header + player_info;
}

/**Reset the menu to invisible, and flags. */
function resumeGame() {
    paused = false;
    inventoryActive = false;
    menu.style.visibility = 'hidden';
}

/**Helper to create html <p></p> tags around text.*/
function createPtag(text) {
    return "<p>" + text + "</p>";
}

/**Helper to create html <li></li> tags around text.*/
function createLiTag(text) {
    return "<li>" + text + "</li>";
}

/**Helper to create html <pre></pre> tags around text.*/
function createPreTag(text) {
    return "<pre>" + text + "</pre>";
}

/**Helper to create HTML buttons for the inventory menu.
 * @param string text : text to convert. Must be a valid, handled string.
 * @param int i : value of the position of the item in the player's inventory.
 * @return string button : HTML string representing the button.
*/
function createActionButtons(text, i) {
    let button = ``;
    let j = i.toString();
    switch(text) {
        case "drink":
            button += `<p><button id="${j}" style="pointer-events:all;">Drink
            </button><button id="drop_${j}" style="pointer-events:all;">Discard
            </button></p>`;
            break;
        case "equip":
            button += `<p><button id="${j}" style="pointer-events:all;">Equip
            </button><button id="drop_${j}" style="pointer-events:all;">Discard
            </button></p>`;
            break;
        case "wear":
            button += `<p><button id="${j}" style="pointer-events:all;">Wear
            </button><button id="drop_${j}" style="pointer-events:all;">Discard
            </button></p>`;
            break;
    }
    return button;
}

/**Draws the inventory menu. */
function drawInventory() {
    pauseGame();
    inventoryActive = true;
    let header = `<div>Game Paused</div><br>`;
    let itemList = "";
    let propertyList = "";
    let actionList = "";
    let potions = [];
    let armors = [];
    let weapons = [];
    for(let i=0; i<inventory.length; i++) {
        let item = inventory[i];
        itemList += createPtag(item.type);
        let property;
        let tmp = "";
        switch(item.type) {
            case "potion":
                tmp = item.health;
                property = "Adds " + tmp.toString() + " health.";
                propertyList += createPtag(property);
                actionList += createActionButtons("drink", i);
                potions.push(i);
                break;
            case "weapon":
                tmp = item.power;
                property = ("Adds " + tmp.toString() +
                            " power. (Current bonus = " +
                            currentWeaponBonus.toString() + ")");
                propertyList += createPtag(property);
                actionList += createActionButtons("equip", i);
                weapons.push(i);
                break;
            case "armor":
                tmp = item.defense;
                property = ("Adds " + tmp.toString() +
                            " defense. (Current bonus = " +
                            currentArmorBonus.toString() + ")");
                propertyList += createPtag(property);
                actionList += createActionButtons("wear", i);
                armors.push(i);
                break;
        }
    }
    let inventory_info = `
        <div style="display: grid; grid-template-columns: 300px 300px 300px;">
            <div>
                <h4>Item:</h4>
                ${itemList}
            </div>
            <div>
                <h4>Properties:</h4>
                ${propertyList}
            </div>
            <div>
                <h4>Action:</h4>
                ${actionList}
            </div>
        </div>
    `;

    menu.innerHTML = header + inventory_info;

    for(let potion of potions) {
        document.getElementById(potion).onclick = (function() {
            drinkPotion(potion);
            display.getContainer().focus();
        });
        let dropID = "drop_" + potion;
        document.getElementById(dropID).onclick = (function() {
            discardItem(potion);
            display.getContainer().focus();
        });
    }

    for(let armor of armors) {
        document.getElementById(armor).onclick = (function() {
            equipArmor(armor);
            display.getContainer().focus();
        });
        let dropID = "drop_" + armor;
        document.getElementById(dropID).onclick = (function() {
            discardItem(armor);
            display.getContainer().focus();
        });
    }

    for(let weapon of weapons){
        document.getElementById(weapon).onclick = (function() {
            equipWeapon(weapon);
            display.getContainer().focus();
        });
        let dropID = "drop_" + weapon;
        document.getElementById(dropID).onclick = (function() {
            discardItem(weapon);
            display.getContainer().focus();
        });
    }
}

/**Draws the super-cool player death skull. */
function drawDeath() {
    menu.style.visibility = 'visible';
    menu.innerHTML = `<div style="display: grid; grid-template-columns: 300px 300px 300px;">
                        <div></div>
                        <div><img src="images/skull.png"
                        style="width:300px; height:375px; justify-items: center;">
                        </img></div>
                        <div></div>    
                    `;
}

// CONSOLE: -------------------------------------------------------------------
/**Prints a message to the visible console.
 * @param string message : text to be printed.
 */
function print(message) {
    clearConsole();
    const MAX_LINES = 5;
    let messageDiv = document.getElementById("messages");
    let msgs = ``;
    messages.push(message);
    while(messages.length > MAX_LINES) {
        messages.shift();
    }
    if(messages.length <= MAX_LINES) {
        for(let i = 0; i < messages.length; i++) {
            msgs += (`${messages[i]}<br>`);
        }
    }
    else {
        for(let i = 0; i < MAX_LINES; i++) {
           msgs += (`${messages[i]}<br>`);
        }
    }
    messageDiv.innerHTML = msgs;
}

function clearConsole() {
    document.getElementById("messages").innerHTML = '';
}

/**Sets up a keyboard handler for the display. */
function setupKeyboardHandler(display) {
    const canvas = display.getContainer();
    const instructions = document.getElementById('instructions');
    canvas.setAttribute('tabindex', "1");
    canvas.addEventListener('keydown', handleKeyDown);
    canvas.addEventListener('blur', () => {
        instructions.textContent = "Click game for keyboard focus";
    });
    canvas.addEventListener('focus', () => {
        instructions.textContent = "Arrow keys to move, ESC for pause menu";
    });
    canvas.focus();
}

// ENTITIES: ------------------------------------------------------------------
/** Holds the glyphs for the entities.
 * @param entityType : must be valid entity.type.
 * @return glyph.
 */
function entityGlyph(entityType) {
    const visuals = {
        player: ['@', "hsl(0, 100%, 50%)"],
        troll: ['T', "hsl(120, 60%, 30%)"],
        orc: ['o', "hsl(100, 30%, 40%)"],
        corpse: ['%', "darkred"],
        potion: ['!', "blue"],
        weapon: [')', "red"],
        armor: [']', "white"],
        gold: ['$', "yellow"],
    };
    return visuals[entityType];
}

/**Creates an entity.
 * @param type valid entity type (required for all entities)
 * @param x x position (required for all entities)
 * @param y y position (required for all entities)
 * @param health health value (for creatures and potions)
 * @param power power value (for creatures and weapons)
 * @param defense defense value (for creatures and armor)
 * @param value value (for gold)
 * @return entity - {id, type, x, y, health, power, defense, value}
 * Entities can be deleted by using the id.
 */
function createEntity(type, x, y, health, power, defense, value) {
    let id = ++createEntity.id;
    let entity = {id, type, x, y, health, power, defense, value};
    entities.set(id, entity);
    return entity;
}

// Helper to get all entities at location x,y:
function allEntitiesAt(x, y) {
    let localEntities = [];
    for(let entity of entities.values()) {
        if(entity.x === x && entity.y === y) {
            localEntities.push(entity);
        }
    }
    return localEntities;
}

// Helper to get blocking entity at location x,y:
function entityAt(x, y) {
    let localEntities = allEntitiesAt(x, y);
    if(localEntities.length > 1) {
        for(let i=0; i<localEntities.length; i++) {
            let entity = localEntities[i];
            if(entity && ENTITY_PROPERTIES[entity.type].blocks) {
                return entity;
            }
        }
    }
    else if(localEntities.length == 1) {
        let entity = localEntities[0];
        if(entity && ENTITY_PROPERTIES[entity.type].blocks) {
            return entity;
        }
    }
    else {
        return null;
    }
}

// Helper to see if a corpse exists at location x,y:
function corpseAt(x, y) {
    let localEntities = allEntitiesAt(x, y);
    if(localEntities.length > 1) {
        for(let i=0; i<localEntities.length; i++) {
            let entity = localEntities[i];
            if(entity && entity.type == "corpse") {
                return true;
            }
        }
    }
    else if(localEntities.length == 1) {
        let entity = localEntities[0];
        if(entity && entity.type == "corpse") {
            return true;
        }
    }
    else {
        return false;
    }
}

/**Helper to get an item at position x,y
 * @return entity item
 */
function itemAt(x, y) {
    let localEntities = allEntitiesAt(x, y);
    if(localEntities.length > 1) {
        for(let i=0; i<localEntities.length; i++) {
            let entity = localEntities[i];
            if(entity && isItem(entity)) {
                return entity;
            }
        }
    }
    else if(localEntities.length == 1) {
        let entity = localEntities[0];
        if(entity && isItem(entity)) {
            return entity;
        }
    }
    else {
        return null;
    }
}

/**Player picks up an item from the ground. */
function pickupItem() {
    if(itemAt(player.x, player.y)) {
        let item = itemAt(player.x, player.y);
        if(item.type == "gold") {
            playerGold += item.value;
            print("Gold acquired! Your beady little eyes gleam with delight.");
            entities.delete(item.id);
        }
        else if(inventory.length < maxItems) {
            inventory.push(item);
            print(item.type + " added to inventory.");
            entities.delete(item.id);
        }
        else {
            print("Your inventory is full.");
        }
    }
}

/**Player discards an item from their inventory.
 *  @param position Int - Position of the item in the global inventory array.
*/
function discardItem(position) {
    print("You hurl the useless " + inventory[position].type +
            " into the wall, shattering it beyond repair.");
    inventory.splice(position, 1);
    drawInventory()
}

/**Player drinks a potion.
 * @param position Int - Position of the item in the global inventory array.
 */
function drinkPotion(position) {
    if(player.health + inventory[position].health
            < ENTITY_PROPERTIES.player.baseHealth) {
        player.health += inventory[position].health;
    }
    else {
        player.health = ENTITY_PROPERTIES.player.baseHealth;
    }
    inventory.splice(position, 1);
    print("Yuck - it tastes of piss. But you do begin to feel better.");
    drawHealthbar();
    drawInventory()
}

/**Player equips armor.
 *  @param position Int - Position of the item in the global inventory array.
 */
function equipArmor(position) {
    if(!armorEquipped){
        player.defense += inventory[position].defense;
        currentArmorBonus = inventory[position].defense;
        armorEquipped = true;
        let msg = "You finally cover your naked hide with some decent";
        msg += " protection. Why did you come down here like that?";
        print(msg);
    }
    else {
        player.defense -= currentArmorBonus;
        player.defense += inventory[position].defense;
        currentArmorBonus = inventory[position].defense;
        let msg = "Discarding your old, foul-smelling armor, you happily don";
        msg += " the shiny new duds.";
        print(msg);
    }
    inventory.splice(position, 1);
    drawInventory()
}

/**Player equips a weapon.
 *  @param position Int - Position of the item in the global inventory array.
 */
function equipWeapon(position) {
    if(!weaponEquipped){
        player.power += inventory[position].power;
        currentWeaponBonus = inventory[position].power;
        weaponEquipped = true;
        let msg = "Smiling visciously at the feel of steel in your powerful";
        msg += " grip, you are ready to get some killing done.";
        print(msg);
    }
    else {
        player.power -= currentWeaponBonus;
        player.power += inventory[position].power;
        currentWeaponBonus = inventory[position].power;
        let msg = "You toss the old blood-soaked weapon and prepare to do ";
        msg += "murder with the new one.";
        print(msg);
    }
    inventory.splice(position, 1);
    drawInventory()
}

// Spawns monsters at dead-ends:
function createMonsters() {
    let monsterCount = 0;
    for(let x = 1; x<winX; x++) {
        for(let y = 1; y<winY; y++) {
            if(isDeadEnd(x, y) && !entityAt(x, y)) {
                let tmp = ROT.RNG.getUniformInt(0,1);
                let type;
                switch(tmp) {
                    case 0:
                        type = "troll";
                        break;
                    case 1:
                        type = "orc";
                        break;
                }
                let monsterHealth = ENTITY_PROPERTIES[type].baseHealth;
                let monsterPower = ENTITY_PROPERTIES[type].basePower;
                let monsterDefense = ENTITY_PROPERTIES[type].baseDefense;
                createEntity(type, x, y, monsterHealth, monsterPower,
                    monsterDefense);
                monsterCount++;
            }
        }
    }
    monsterCountInt = monsterCount;
}

// Spawns items randomly.
function createItems() {
    let itemCount = ROT.RNG.getUniformInt(50,100);
    itemCountInt = itemCount;
    for(let i=0; i<itemCount; i++) {
        let x = ROT.RNG.getUniformInt(1,winX);
        let y = ROT.RNG.getUniformInt(1,winY);
        if(!entityAt(x, y) && map.get(x, y) === 0) {
            let tmp = ROT.RNG.getUniformInt(0,3);
            let type;
            let health = 0;
            let power = 0;
            let defense = 0;
            let value = 0;
            switch(tmp) {
                case 0:
                    type = "potion";
                    health = ROT.RNG.getUniformInt(50,100);
                    break;
                case 1:
                    type = "weapon";
                    power = ROT.RNG.getUniformInt(5,15);
                    break;
                case 2:
                    type = "armor";
                    defense = ROT.RNG.getUniformInt(5,15);
                    break;
                case 3:
                    type = "gold";
                    value = ROT.RNG.getUniformInt(50,100);
                    break;
            }
            createEntity(type, x, y, health, power, defense, value);
            i++;
        }
    }
}

/**Helper to detect whether an attacker can see a defender.
 * @param attacker - entity
 * @param defender - entity
 * @return boolean
 */
function canSee(attacker, defender) {
    let lightMap = computeLightMap(attacker.x, attacker.y);
    let lit = lightMap.get(map.key(defender.x, defender.y)) > 0.0;
    if(lit) {
        return true;
    }
    return false;
}

/**Helper to detect whether an entity is an item.
 * @param entity
 * @return boolean
 */
function isItem(entity) {
    if(entity.type == 'potion' ||
        entity.type == 'weapon' ||
        entity.type == 'armor' ||
        entity.type == 'gold') {
        return true;
    }
    return false;
}

/**Moves all enemies if they can see the player. */
function enemiesMove() {
    for (let entity of entities.values()) {
        if (entity.type !== 'player' && entity.type !== 'corpse' &&
                !isItem(entity) && canSee(entity, player)) {
            let attackDijkstra = new ROT.Path.Dijkstra(player.x, player.y,
                passableCallback, {topology:4});
            let attackPath = [];
            let attackPathCallback = function(x, y) {
                attackPath.push([x, y]);
            }
            attackDijkstra.compute(entity.x, entity.y, attackPathCallback);
            let tmp = attackPath[1];
            try {
                let x = tmp[0];
                let y = tmp[1];
                let target = entityAt(x, y);
                if(!target && !corpseAt(x, y)) {
                    entity.x = x;
                    entity.y = y;
                }
                else if(target === player) {
                    attack(entity, player);
                }
                else if(corpseAt(x, y)) {
                    if(attackPath.length > 2) {
                        entity.x = x;
                        entity.y = y;
                    }
                }
            }
            catch(err) {
                console.log(err);
            }
        }
    }
}

/**Kills an entity. If the entity is player, end the game. Otherwise, turn
 * the entity into a corpse.
 * @param entity
 */
function killEntity(entity) {
    if(entity.type == 'player') {
        gameOver = true;
        playerKilled = true;
    }
    else {
        entity.type = "corpse";
    }
}

/**Applies damage during combat, calling killEntity if needed.
 * @param defender - entity
 * @param damage - int
 */
function takeDamage(defender, damage) {
    print(damage + " damage dealt to " + defender.type + ".\n");
    if(damage >= defender.health) {
        defender.health -= damage;
        if(defender.type == "player") {
            print("The Mazefighter has been slain!\n");
        }
        else {
            print("The " + defender.type + " has been slain!");
        }
        killEntity(defender);
    }
    else {
        defender.health -= damage;
    }
}

/* attack function could use improvement. ATM it just adds +- small random
    value to calculate whether damage is done and how much.*/
function attack(attacker, defender) {
    let randomModifier = ROT.RNG.getUniformInt(0,5);
    let toModify = randomTruth();
    let damage;
    if(toModify) {
        let posOrNeg = randomTruth();
        if(posOrNeg) {
            damage = attacker.power - defender.defense + randomModifier;
        }
        else {
            damage = attacker.power - defender.defense - randomModifier;
        }
    }
    else {
        damage = attacker.power - defender.defense;
    }
    if(damage > 0) {
        let msg = attacker.type + " lands a bloody blow on ";
        msg += defender.type + ", sending him reeling!";
        print(msg);
        takeDamage(defender, damage);
    }
    else {
        let msg = attacker.type + " swings at ";
        msg += defender.type + " but misses.";
        print(msg);
    }
}

// KEYBOARD: ------------------------------------------------------------------
// Define actions for specific Keyboard events:
function handleKeys(keyCode) {
    const actions = {
        [ROT.KEYS.VK_RIGHT]:  () => ['move', +1, 0],
        [ROT.KEYS.VK_LEFT]:   () => ['move', -1, 0],
        [ROT.KEYS.VK_DOWN]:   () => ['move', 0, +1],
        [ROT.KEYS.VK_UP]:     () => ['move', 0, -1],
        [ROT.KEYS.VK_RETURN]: () => ['enter', 0, 0],
        [ROT.KEYS.VK_ESCAPE]: () => ['escape', 0, 0],
        [ROT.KEYS.VK_I]: () => ['inventory', 0, 0],
        [ROT.KEYS.VK_G]: () => ['pickup', 0, 0],
    };
    let action = actions[keyCode];
    return action ? action() : undefined;
}

// This function is sort of a 'main' - the game loop logic lives here:
function handleKeyDown(event) {
    let action = handleKeys(event.keyCode);
    if (action) {
        if(gameOver == true && action[0] === 'enter' && playerKilled) {
            location.reload();
        }
        else if(gameOver == true && action[0] === 'enter' && !playerKilled) {
            newLevel();
        }
        else if(!paused && action[0] == 'escape') {
            drawMenu();
        }
        else if(paused && action[0] == 'escape') {
            resumeGame();
        }
        else if(action[0] == 'inventory') {
            drawInventory();
        }
        else if(!paused && action[0] == 'pickup') {
            pickupItem();
        }
        else if (action[0] === 'move' && gameOver == false &&
                paused == false) {
            let [_, dx, dy] = action;
            let newX = player.x + dx,
                newY = player.y + dy;
            if (map.get(newX, newY) === 0) {
                let target = entityAt(newX, newY);
                if(target && ENTITY_PROPERTIES[target.type].blocks) {
                    attack(player, target);
                }
                else {
                    player.x = newX;
                    player.y = newY;
                    moveCount++;
                    playerPath.push([newX, newY]);
                    if(newX == winX && newY == winY) {
                        print("Exit reached.");
                        gameOver = true;
                    }
                    if(itemAt(newX, newY)) {
                        let item = itemAt(newX, newY);
                        itemHere = true;
                        let msg = "There is a " + item.type;
                        msg += " here. Press 'g' to pick it up."
                        print(msg);
                    }
                    else {
                        itemHere = false;
                    }
                }
                enemiesMove();
            }
            draw();
            if(gameOver == true) {
                if(!playerKilled) {
                    endGame();
                }
                else {
                    endGameDefeat();
                }
            }
        }
        else {
            throw `unhandled action ${action}`;
        }
        event.preventDefault();
    }
}

// MAP: -----------------------------------------------------------------------
function createMap(width, height) {
    let map = {
        width, height,
        tiles: new Map(),
        key(x, y) {return `${x},${y}`;},
        get(x, y) {return this.tiles.get(this.key(x, y));},
        set(x, y, value) {this.tiles.set(this.key(x, y), value);},
    };
    // what kind of maze do we want?
    let mazeType = ROT.RNG.getUniformInt(0, 2);
    let maze;
    switch(mazeType) {
        case 0:
            mazeTypeString = "Eller";
            maze = new ROT.Map.EllerMaze(width, height);
            break;
        case 1:
            let iceyValue = ROT.RNG.getUniformInt(0, 5);
            mazeTypeString = "Icey " + iceyValue;
            maze = new ROT.Map.IceyMaze(width, height, iceyValue);
            break;
        case 2:
            mazeTypeString = "Divided";
            maze = new ROT.Map.DividedMaze(width, height);
            break;
    }
    maze.create((x, y, contents) => map.set(x, y, contents));
    // Divided maze has a bad row on the right side we must fix:
    if(mazeType === 2) {
        for(let i=0; i<=winY; i++) {
            map.set(winX+1, i, 1);
        }
    }
    return map;
}

// helper function to tell whether a cell is a dead end:
function isDeadEnd(x, y) {
    let cornerCount = 0;
    if(map.get(x, y) === 0) { // is cell open
        if(map.get(x+1, y) === 1) { // is East closed
            cornerCount += 1;
        }
        if(map.get(x-1, y) === 1) { // is West closed
            cornerCount += 1;
        }
        if(map.get(x, y+1) === 1) { // is North closed
            cornerCount += 1;
        }
        if(map.get(x, y-1) === 1) { // is South closed
            cornerCount += 1;
        }
        if(cornerCount < 3) {
            return false;
        }
        return true;
    }
}

// helper to determine whether cell is outer wall:
function isOuterWall(x, y) {
    if(x <=1 || y <=1 || x >= winX || y >= winY) {
        return true;
    }
    else {
        return false;
    }
}

// dig out a room from (x,y) to radius=roomSize
function digRoom(x, y, roomSize) {
    if(!isOuterWall(x, y)) {
        for(let i=1; i< roomSize; i++) {
            if(!isOuterWall(x+i, y)) // dig right
            {
                map.set(x+i, y, 0);
            }
            if(!isOuterWall(x-i, y)) // dig left
            {
                map.set(x-i, y, 0);
            }
            if(!isOuterWall(x, y+i)) // dig up
            {
                map.set(x, y+i, 0);
            }
            if(!isOuterWall(x, y-i)) // dig down
            {
                map.set(x, y-i, 0);
            }
            if(!isOuterWall(x+i, y+i)) // dig up-right
            {
                map.set(x+i, y+i, 0);
            }
            if(!isOuterWall(x-i, y+i)) // dig up-left
            {
                map.set(x-i, y+i, 0);
            }
            if(!isOuterWall(x+i, y-i)) // dig down-right
            {
                map.set(x+i, y-i, 0);
            }
            if(!isOuterWall(x-i, y-i)) // dig down-left
            {
                map.set(x-i, y-i, 0);
            }
        }
    }
}

/**Changes a wall into an empty cell. */
function digHole(x, y) {
    if(map.get(x, y) === 1) {
        map.set(x, y, 0);
    }
}

// returns random bool:
function randomTruth() {
    if(ROT.RNG.getUniformInt(0,1) === 1) {
        return true;
    }
    else {
        return false;
    }
}

// At random, choose whether to dig rooms, holes, or nothing:
function makeMazeInteresting() {
    if(randomTruth()) {
        let rooms = ROT.RNG.getUniformInt(1, 10);
        let roomSize = ROT.RNG.getUniformInt(2, 10);
        roomCountInt = rooms;
        roomSizeInt = roomSize;
        for(let i = 0; i<rooms; i++) {
            let x = ROT.RNG.getUniformInt(2, winX-1);
            let y = ROT.RNG.getUniformInt(2, winY-1);
            digRoom(x, y, roomSize);
        }
    }
    else if(randomTruth()) {
        let holeCount = ROT.RNG.getUniformInt(100, 400);
        holeCountInt = holeCount;
            for(let i = 0; i<holeCount; i++) {
                let x = ROT.RNG.getUniformInt(1, winX);
                let y = ROT.RNG.getUniformInt(1, winY);
                digHole(x, y);
            }
    }
}

/* A hack to help keep track of whether areas have been explored:
   @return a 2-dimensional array of boolean values
   This is initialized only once when the game starts, stored in a
   global named 'exploration', then modified only during the draw() function,
   when the player's lightmap is computed. Basically, if the player has ever
   seen a tile, it is considered explored.
*/
function createExplorationMap() {
    let exploration = [];
    for(let i=0; i<map.width; i++) {
        for(let j=0; j<map.height; j++) {
            exploration.push([false]);
        }
    }
    return exploration;
}

// END GAME: ------------------------------------------------------------------
/**This currently always happens if the player makes it to the exit. Needs to
 * be refactored to deal with level-switching. */
function endGame() {
    let victory = "Congratulations! You have been found worthy.";
    victory += " Ninja bonus granted!";
    let defeat = "You have failed to find the shortest path.";
    let stats = "\tShortest path: " + shortestPath;
    stats += "\tYour move count: " + moveCount;
    if(moveCount > shortestPath) {
        print(defeat + stats);
    }
    else {
        print(victory + stats);
    }
    print("Press ENTER / RETURN to go again.");
}

/**This happens if the player dies. */
function endGameDefeat() {
    drawDeath();
    let msg = "As the fiends of the depths feast on your gurgling flesh";
    msg += " - the agony endless and unbearable -";
    print(msg);
    print("your short life flashes before your eyes.");
    print("You have died!");
    print("Press ENTER / RETURN to go again.");
}

// DRAW: ----------------------------------------------------------------------
/**For non-player entities only, player's lightmap is done inside draw().
 * This gets called from the canSee() function.
*/
function computeLightMap(x, y) {
    let lightMap = new Map(); // map key to 0.0–1.0
    fov.compute(x, y, 10, (x, y, r, visibility) => {
        lightMap.set(map.key(x, y), visibility);
    });
    return lightMap;
}

/**This one is interesting and took me a minute to get just right.
 * I ended up making two maps, the glyphMap is what actually gets returned,
 * and the setMap is a helper which stores the entity type as its value.
 * When we try to add a glyph, we first check to see if the x,y coords already
 * exist. If so, then we consult the setMap to see what the entity type is,
 * and check if it is a corpse. If it is, then it needs to be overwritten
 * with the new entity so that corpses do not get rendered on top of living
 * entities.
 * Bug SEEMS to be fixed now. Problem was, js stores my keys x,y as strings,
 * so setMap.get(player.x, player.y) was returning undefined. My ugly fix
 * was to craft a custom key string to look like:
 * "x,y".
 */
function computeGlyphMap() {
    let glyphMap = new Map();
    let setMap = new Map();
    for(let entity of entities.values()) {
        if(!glyphMap.has(map.key(entity.x, entity.y))) {
            glyphMap.set(map.key(entity.x, entity.y),
                entityGlyph(entity.type));
            setMap.set(map.key(entity.x, entity.y), entity.type);
        }
        else {
            let tmpX = entity.x;
            let tmpY = entity.y;
            let tmpKey = tmpX.toString() + "," + tmpY.toString();
            let tmp = setMap.get(tmpKey);
            if(tmp == "corpse" && entity.type != "corpse") {
                glyphMap.set(map.key(entity.x, entity.y),
                    entityGlyph(entity.type));
                setMap.set(map.key(entity.x, entity.y), entity.type);
            }
        }
    }
    return glyphMap;
}

/**Draw() */
function draw() {
    display.clear();

    drawHealthbar();

    // calculate Player's light map:
    let lightMap = new Map();
    fov.compute(player.x, player.y, 10, (x, y, r, visibility) => {
        lightMap.set(map.key(x, y), visibility);
        // set explored flag on cells which have been seen:
        if(visibility > 0.0) {
            exploration[x][y] = true;
        }
    });

    let glyphMap = computeGlyphMap();

    const mapColors = {
        [false]: {[false]: "rgb(50, 50, 150)", [true]: "rgb(0, 0, 100)"},
        [true]: {[false]: "rgb(200, 180, 50)", [true]: "rgb(130, 110, 50)"}
    };
    for (let y = 0; y < map.height; y++) {
        for (let x = 0; x < map.width; x++) {
            // we only need to draw tiles which are explored:
            let tile = exploration[x][y];
            if(!tile) {continue;}

            let lit = lightMap.get(map.key(x, y)) > 0.0,
                wall = map.get(x, y) !== 0;
            let ch = ' ',
                fg = "black",
                bg = mapColors[lit][wall];
            let glyph = glyphMap.get(map.key(x, y));
            if (glyph) {
                ch = lit? glyph[0] : ch;
                fg = glyph[1];
                bg = glyph[2] || bg;
            }
            display.draw(x, y, ch, fg, bg);
        }
    }
    // highlight the exit:
    display.draw(winX, winY, "", "", "#3f3");

    // highlight the dijkstra and player paths at game over:
    if(gameOver == true && !playerKilled) {
        for(let i in playerPath) {
            let tmp = playerPath[i];
            let x = tmp[0];
            let y = tmp[1];
            display.draw(x, y, "", "", "#FF0000");
        }
        for(let i in path) {
            let tmp = path[i];
            let x = tmp[0];
            let y = tmp[1];
            display.draw(x, y, "", "", "#7FFF00");
        }
    }
}

/**playing with injecting a small delay when writing to the console div,
 * I may or may not keep this, depending on how much I can improve the
 * way that div is displayed:
 */
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function greetPlayer() {
    let lines = [];
    let msg = "You are in a maze of twisty little passages... How did you get";
    lines.push(msg);
    msg = " here? You cannot seem to remember. But you can sense that ";
    lines.push(msg);
    msg = "wherever 'here' is, you don't want to stay very long. The scent ";
    lines.push(msg);
    msg = "of blood lingers in the dank air, and the scent of something...";
    lines.push(msg);
    msg = " Worse... You can hear faint scraping sounds, and a horrid, ";
    lines.push(msg);
    msg = " raspy gurgling that makes your skin crawl. 'Please', you whisper";
    lines.push(msg);
    msg = " softly. 'Please let me wake up...' Get to the exit, Mazefighter.";
    lines.push(msg);
    for(let line of lines) {
        await sleep(1000);
        print(line);
    }
}

// GAME BEGIN:-----------------------------------------------------------------
function beginPlay() {
    document.getElementById('game').appendChild(display.getContainer());
    resumeGame();
    createEntity.id = 0;
    greetPlayer();
    setupKeyboardHandler(display);
    createMonsters();
    createItems();
    drawGameBorders();
    draw();
}

//  START NEW LEVEL:-----------------------------------------------------------
/**Prints greeting for new level. */
async function newLevelGreeting() {
    let lines = [];
    let msg = "As you descend further into the depths, a sense of forboding";
    lines.push(msg);
    msg = " washes over you. Even though you managed to wade through so many";
    lines.push(msg);
    msg = " freakish monsters, you know that the hordes are legion.";
    lines.push(msg);
    msg = " And they are still hungry...";
    lines.push(msg);
    for(let line of lines) {
        await sleep(1000);
        print(line);
    }
}

/**Deletes all entities which are not the player. */
function resetEntities() {
    for(let entity of entities.values()) {
        if(entity !== player) {
            entities.delete(entity.id);
        }
    }
}

/**Resets globals which need to be discarded for a new level.
 * Also recalculates shortest path, which requires call to makeMazeInteresting.
 */
function resetGlobalVariables() {
    gameOver = false;
    player.x = 1;
    player.y = 1;
    moveCount = 0;
    playerPath = [];
    fov = new ROT.FOV.PreciseShadowcasting((x, y) => map.get(x, y) === 0);
    map = createMap(WIDTH, HEIGHT);
    exploration = createExplorationMap();
    makeMazeInteresting();
    dijkstra = new ROT.Path.Dijkstra(1, 1, passableCallback, {topology:4});
    path = [];
    dijkstra.compute(winX, winY, PathCallback);
    shortestPath = path.length-1;
    dungeonLevel += 1;
}

/**Sets up a new level. */
function newLevel() {
    newLevelGreeting();
    resetEntities();
    resetGlobalVariables();
    createMonsters();
    createItems();
    draw();
}

/**----------------------------------------------------------------------------
 | Begin play:                                                                |
 | This stuff below needs to be refactored to deal with level-switching,      |
 | see refactor_notes.js and scratchpad.js for my notes on where I'm at with  |
 | this.                                                                      |
 ----------------------------------------------------------------------------*/
// GLOBAL CONSTANTS:
const WIDTH = 60;
const HEIGHT = 25;
const display = new ROT.Display({width: WIDTH, height: HEIGHT,
        forceSquareRatio:true});
const winX = WIDTH-3;
const winY = HEIGHT-2;
const ENTITY_PROPERTIES = {
    player: {blocks: true, baseDefense: 10, basePower: 25, baseHealth: 300,
        value: 0},
    troll: {blocks: true, baseDefense: 15, basePower: 20, baseHealth: 40,
        value: 0},
    orc: {blocks: true, baseDefense: 10, basePower: 15, baseHealth: 25,
        value: 0},
    corpse: {blocks: false},
    potion: {blocks: false, baseDefense: 0, basePower: 0, baseHealth: 0,
        value: 0},
    weapon: {blocks: false, baseDefense: 0, basePower: 0, baseHealth: 0,
        value: 0},
    armor: {blocks: false, baseDefense: 0, basePower: 0, baseHealth: 0,
        value: 0},
    gold: {blocks: false, baseDefense: 0, basePower: 0, baseHealth: 0,
        value: 0},
};

// GLOBAL VARIABLES:
let messages = [];
let healthbar = document.getElementById("healthbar");
let paused = false;
let inventoryActive = false;
let menu = document.getElementById("menu");
let entities = new Map();
let player = createEntity('player', 1, 1, ENTITY_PROPERTIES.player.baseHealth,
    ENTITY_PROPERTIES.player.basePower, ENTITY_PROPERTIES.player.baseDefense);
let playerKilled = false;
let inventory = [];
let maxItems = 6;
let playerGold = 0;
let armorEquipped = false;
let currentArmorBonus = 0;
let weaponEquipped = false;
let currentWeaponBonus = 0;
let moveCount = 0;
let playerPath = [];
let gameOver = false;
let itemHere = false;
let fov = new ROT.FOV.PreciseShadowcasting((x, y) => map.get(x, y) === 0);
let mazeTypeString = "";
let map = createMap(WIDTH, HEIGHT);
let exploration = createExplorationMap();
let passableCallback = function(x, y) {
    return map.get(x, y) === 0;
}
let dungeonLevel = 1;
let playerLevel = 1;
let roomSizeInt = 0;
let roomCountInt = 0;
let holeCountInt = 0;
let itemCountInt = 0;
let monsterCountInt = 0;

// dijkstra shortest path initialization for game start:
makeMazeInteresting();
let dijkstra = new ROT.Path.Dijkstra(1, 1, passableCallback, {topology:4});
let path = [];
let PathCallback = function(x, y) {
    path.push([x, y]);
}
dijkstra.compute(winX, winY, PathCallback);
let shortestPath = path.length-1;

// START THE GAME:
beginPlay();

