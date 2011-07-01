#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

amateurradio_mod = Extension('amateurradio',
    libraries = ['ax25'],
    sources = ['src/amateurradio.c'])

setup(name = "python-amateurradio",
    version = "1.0",
    description = "Amateur Radio functions",
    author = "Alejandro Santos",
    author_email = "alejolp@alejolp.com.ar",
    url = "http://github.com/alejolp/python-amateurradio",
    ext_modules = [amateurradio_mod])


