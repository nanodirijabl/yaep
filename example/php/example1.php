<?php

declare(strict_types=1);

use Yaep\Node;
use Yaep\Term\AtomTerm;
use Yaep\Term\BinaryTerm;
use Yaep\Term\TupleTerm;

$node = new Node('php'.random_int(0, 99), 'secretcookie');
$conn = $node->connect('srv@127.0.0.1', 1000);

var_dump(sprintf('Start at %s', date('H:i:s', time())));
while (true) {
    $ts = time();

    if (null === $message = $conn->receive(2000)) {
        var_dump(sprintf('No new message since %s', date('H:i:s', $ts)));
        continue;
    }

    if ($message instanceof AtomTerm) {
        var_dump('received atom: '.$message->toString());
        continue;
    }

    if (!$message instanceof TupleTerm || 2 !== $message->getArity()) {
        var_dump('unexpected message:', $message);
        continue;
    }

    [$from, $content] = $message->toArray();
    var_dump([$from, $content]);

    $atom = new AtomTerm('ping');
    $conn->send($from, $atom, 100);

    $bin = new BinaryTerm('ping ping ping');
    $selfPid = $conn->getPid();

    $term = new TupleTerm($atom, $selfPid, $bin);
    // $term = new TupleTerm(  $bin);
    $conn->send($from, $term, 100);

    // $conn2->send($from, new TupleTerm(new AtomTerm('ping'), $conn2->getPid(), new BinaryTerm('ping ping ping')), 100);
}
