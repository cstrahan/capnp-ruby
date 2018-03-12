#!/in/bash

set -e

CAPNPROTO_RELEASE_URL="${CAPNPROTO_RELEASE_URL:-https://github.com/OneSignal/capnproto-debian/releases/download/onesignal-0.6.1-1}"
CAPNPROTO_DEB="${CAPNPROTO_DEB:-capnproto_0.6.1-1_amd64.deb}"
LIBCAPNP_DEB="${LIBCAPNP_DEB:-libcapnp-0.6.1_0.6.1-1_amd64.deb}"
LIBCAPNP_DEV_DEB="${LIBCAPNP_DEV_DEB:-libcapnp-dev_0.6.1-1_amd64.deb}"
TRAVIS_BUILD_DIR="${TRAVIS_BUILD_DIR:-../}"
BUILD_DIR="${BUILD_DIR:-/capnp-ruby}"

echo "CAPNPROTO_RELEASE_URL:    ${CAPNPROTO_RELEASE_URL}"
echo "CAPNPROTO_DEB:            ${CAPNPROTO_DEB}"
echo "LIBCAPNP_DEB:             ${LIBCAPNP_DEB}"
echo "LIBCAPNP_DEV_DEB:         ${LIBCAPNP_DEV_DEB}"

cat >Dockerfile <<EOF
FROM ruby:2.4

RUN \
    echo "deb http://deb.debian.org/debian sid main" > /etc/apt/sources.list.d/sid.list && \
    apt-get update && \
    apt-get install --yes --no-install-recommends git curl bzip2 gcc-7 g++-7

RUN \
    curl -sSLO "${CAPNPROTO_RELEASE_URL}/${CAPNPROTO_DEB}" && \
    curl -sSLO "${CAPNPROTO_RELEASE_URL}/${LIBCAPNP_DEB}" && \
    curl -sSLO "${CAPNPROTO_RELEASE_URL}/${LIBCAPNP_DEV_DEB}" && \
    dpkg -i ${CAPNPROTO_DEB} ${LIBCAPNP_DEB} ${LIBCAPNP_DEV_DEB}

WORKDIR ${BUILD_DIR}
COPY . .

RUN \
    export CXX="g++-7" && \
    gem install gem-compiler && \
    gem build capn_proto.gemspec && \
    gem compile \$(ls capn_proto-*.gem) --prune &&\
    ls -1 *.gem > ./artifacts
EOF

TAG="onesignal/capnp-ruby"

docker build --tag="${TAG}" --file Dockerfile .

CIDFILE="/tmp/capnp-ruby.$(date '+%s')"
rm -f ${CIDFILE}
ARGS="--cidfile=${CIDFILE}"

docker run ${ARGS} "${TAG}"
CID=$(cat ${CIDFILE})

mkdir -p "${TRAVIS_BUILD_DIR}"
docker cp ${CID}:"${BUILD_DIR}/artifacts" .

cat artifacts | while read artifact
do
    echo "Artifact: ${artifact}"
    docker cp ${CID}:"${BUILD_DIR}/${artifact}" "${TRAVIS_BUILD_DIR}"
done

docker rm -f ${CID} >/dev/null
rm -f ${CIDFILE} artifacts
