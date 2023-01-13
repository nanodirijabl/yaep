FROM php:8.1-zts-alpine3.16 as php

# Copy pre-built Erlang
COPY --from=elixir:1.13.4-alpine /usr/local/lib/erlang /usr/local/lib/erlang
# Copy pre-built Elixir
COPY --from=elixir:1.13.4-alpine /usr/local/lib/elixir /usr/local/lib/elixir
# Copy pre-built binaries (and symlinks)
COPY --from=elixir:1.13.4-alpine /usr/local/bin/ /usr/local/bin/

COPY . /usr/local/src/yaep

RUN \
    # Build and enable php bridge extension
    apk add --virtual .build-deps $PHPIZE_DEPS \
    && cd /usr/local/src/yaep \
    && phpize \
    && ./configure --with-erlang-interface=/usr/local/lib/erlang/lib/erl_interface-5.2.2 \
    && make clean \
    && make \
    && make install \
    && apk del .build-deps \
    && rm -rf /usr/local/src/yaep \
    && docker-php-ext-enable yaep \
    && \
    # Install erlang runtime dependencies
    runDeps="$( \
        scanelf --needed --nobanner --format '%n#p' --recursive /usr/local \
            | tr ',' '\n' \
            | sort -u \
            | awk 'system("[ -e /usr/local/lib/" $1 " ]") == 0 { next } { print "so:" $1 }' \
    )" \
    && apk add --virtual .erlang-rundeps $runDeps libstdc++ lksctp-tools ca-certificates

CMD ["iex"]