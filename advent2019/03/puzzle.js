function Puzzle() {
}
Puzzle.prototype.parse = (lines) => {
  return lines;
  return lines.map((line) => parseInt(line)).filter((num) => num === num);
};
function isPositionSeen(
    seenPositions = new Map([[0, new Map([[0, 0]])]]),
    position = {x: 0, y: 0, steps: 0},
    canUpdate = true) {
  if (seenPositions.has(position.x) && seenPositions.get(position.x).has(position.y)) return true;
  if (canUpdate) {
    if (!seenPositions.has(position.x)) seenPositions.set(position.x, new Map());
    seenPositions.get(position.x).set(position.y, position.steps);
  }
  return false;
}
function updatePositions(
    wire = 0,
    seenPositions = new Map([[0, new Map([[0, 0]])]]),
    bestIntersected = {x: 0, y: 0, steps: 0},
    position = {x: 0, y: 0, steps: 0}) {
  if (wire === 0) {
    isPositionSeen(seenPositions, position, true); // just to update seen positions
    return;
  }
  if (isPositionSeen(seenPositions, position, false)) { // not updating seen positions here
    const currentSteps = position.steps + seenPositions.get(position.x).get(position.y);
    //console.log('got intersection, position = ', position, ' steps from other wire = ', currentSteps - position.steps);
    const previousSteps = bestIntersected.steps;
    if (previousSteps === 0 || currentSteps < previousSteps) {
      bestIntersected.x = position.x;
      bestIntersected.y = position.y;
      bestIntersected.steps = currentSteps;
      //console.log('updated bestIntersected = ', bestIntersected);
    }
  }
}
Puzzle.prototype.solve_p2 = (data = ['', '']) => {
  let seenPositions = new Map([[0, new Map([[0, 0]])]]);
  let bestIntersected = {x: 0, y: 0, steps: 0};
  let position = {x: 0, y: 0, steps: 0};
  //console.log('bestIntersected = ', bestIntersected);
  for (let wire = 0; wire < 2; wire++) {
    position.x = 0;
    position.y = 0;
    position.steps = 1;
    data[wire].split(',').reduce((heading, move) => {
      if (move[0] === 'U') heading = 0;
      else if (move[0] === 'R') heading = 90;
      else if (move[0] === 'D') heading = 180;
      else if (move[0] === 'L') heading = 270;
      let x = 0, y = 0;
      switch (heading) {
        case 0:
        default:
          for (y = position.y + 1; y <= position.y + parseInt(move.substr(1)); ++y, ++(position.steps))
            updatePositions(wire, seenPositions, bestIntersected, {x: position.x, y: y, steps: position.steps});
          position.y = y - 1;
          //console.log('position = ', position);
          break;
        case 90:
          for (x = position.x + 1; x <= position.x + parseInt(move.substr(1)); ++x, ++(position.steps))
            updatePositions(wire, seenPositions, bestIntersected, {x: x, y: position.y, steps: position.steps});
          position.x = x - 1;
          //console.log('position = ', position);
          break;
        case 180:
          for (y = position.y - 1; y >= position.y - parseInt(move.substr(1)); --y, ++(position.steps))
            updatePositions(wire, seenPositions, bestIntersected, {x: position.x, y: y, steps: position.steps});
          position.y = y + 1;
          //console.log('position = ', position);
          break;
        case 270:
          for (x = position.x - 1; x >= position.x - parseInt(move.substr(1)); --x, ++(position.steps))
            updatePositions(wire, seenPositions, bestIntersected, {x: x, y: position.y, steps: position.steps});
          position.x = x + 1;
          //console.log('position = ', position);
          break;
      }
      return heading;
    }, 0);
  }
  //console.log('bestIntersected = ', bestIntersected);
  return bestIntersected.steps;
}
module.exports = Puzzle;
