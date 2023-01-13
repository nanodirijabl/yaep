<?php

/** @generate-class-entries */

namespace Yaep\Term {

    abstract class AbstractTerm
    {
    }

    final class AtomTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(string $atom)
        {
        }

        public function toString(): string
        {
        }
    }

    final class BinaryTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(string $binary)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function toString(): mixed
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function getSize(): int
        {
        }
    }

    final class BitBinaryTerm extends AbstractTerm
    {
    }

    final class IntegerTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(int $value)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function getValue(): int
        {
        }
    }

    final class FloatTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(float $value)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function getValue(): float
        {
        }
    }

    final class StringTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(string $value)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function getValue(): string
        {
        }
    }

    final class TupleTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(AbstractTerm ...$items)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function getArity(): int
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function toArray(): array
        {
        }
    }

    final class ListTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(AbstractTerm ...$items)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function getSize(): int
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function toArray(): array
        {
        }
    }

    final class MapTerm extends AbstractTerm
    {
        /**
         * @throws \Yaep\TermEncodingException
         */
        public function __construct(AbstractTerm ...$kvPairs)
        {
        }

        /**
         * @throws \Yaep\TermDecodingException
         */
        public function toArray(): array
        {
        }
    }

    final class RefTerm extends AbstractTerm
    {
    }

    final class PortTerm extends AbstractTerm
    {
    }

    final class FunctionTerm extends AbstractTerm
    {
    }

    final class PidTerm extends AbstractTerm
    {
    }
}

namespace Yaep {

    final class NodeInitializationException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class NodeConnectionException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class NodeCreateProcessIdentifierException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class MessageReceivingException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class MessageSendingException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class TermEncodingException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class TermDecodingException extends \RuntimeException
    {
        public function __construct()
        {
        }
    }

    final class Connection
    {
        public function getPid(): Term\PidTerm
        {
        }

        /**
         * @throws MessageReceivingException
         * @throws TermDecodingException
         */
        public function receive(int $timeout): ?Term\AbstractTerm
        {
        }

        /**
         * @throws MessageSendingException
         * @throws TermEncodingException
         */
        public function send(Term\PidTerm $pid, Term\AbstractTerm $message, int $timeout): void
        {
        }
    }

    final class Node
    {
        /**
         * @throws NodeInitializationException
         */
        public function __construct(string $name, string $cookie)
        {
        }

        /**
         * @throws NodeConnectionException
         */
        public function connect(string $node, int $timeout): Connection
        {
        }
    }
}
