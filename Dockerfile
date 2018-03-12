FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y software-properties-common python-software-properties
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get -yq install gcc-7 g++-7 git curl make libssl-dev libreadline-dev zlib1g-dev

RUN update-alternatives --quiet \
  --install /usr/bin/gcc gcc /usr/bin/gcc-7 10 \
  --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
  --slave /usr/bin/gcov gcov /usr/bin/gcov-7
RUN update-alternatives --quiet --set gcc /usr/bin/gcc-7

RUN apt-get install -y bzip2
RUN apt-get install -y build-essential
# ruby
RUN git clone https://github.com/rbenv/rbenv.git /usr/local/.rbenv
ENV PATH /usr/local/.rbenv/bin:$PATH
RUN eval "$(rbenv init -)"

RUN git clone https://github.com/rbenv/ruby-build.git ~/.rbenv/plugins/ruby-build
RUN echo 'export PATH="$HOME/.rbenv/plugins/ruby-build/bin:$PATH"' >> ~/.bashrc
RUN export PATH="$HOME/.rbenv/plugins/ruby-build/bin:$PATH"
RUN rbenv install 2.4.1 && rbenv global 2.4.1
RUN apt-get install -y ruby-full

RUN gem install bundler -v 1.16.0ex
RUN rbenv rehash

RUN curl -O https://capnproto.org/capnproto-c++-0.6.1.tar.gz \
    && tar zxf capnproto-c++-0.6.1.tar.gz \
    && cd capnproto-c++-0.6.1 \
    && ./configure \
    && make -j6 check \
    && make install

RUN ln -sf /usr/bin/g++-7 /usr/bin/g++ && ln -sf /usr/bin/gcc-7 /usr/bin/gcc

