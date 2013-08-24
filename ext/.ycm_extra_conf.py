# vim: ts=2 et sw=2 sts=2

import os
import ycm_core
import glob
import subprocess

def RubyInclude():
  cmd = ["ruby", "-e", "print RbConfig::CONFIG['rubyhdrdir']"]
  process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  rubyhdrdir = process.stdout.read()
  return rubyhdrdir

def RiceInclude():
  rice_path_helper = """
  def locate_gem(name)
    spec = Bundler.load.specs.find{|s| s.name == name }
    raise GemNotFound, "Could not find gem '#{name}' in the current bundle." unless spec
    if spec.name == 'bundler'
      return File.expand_path('../../../', __FILE__)
    end
    spec.full_gem_path
  end

  print locate_gem("rice")
  """
  cmd = ["bundle", "exec", "ruby", "-e", rice_path_helper]
  process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  ricehdrdir = os.path.join(process.stdout.read(), "ruby/lib/include/")
  return ricehdrdir

flags = [
'-Wall',
'-Wextra',
'-Werror',
'-fexceptions',
'-Wc++98-compat',
'-std=c++11',
'-x', 'c++',
'-I', '.',
'-I', '/usr/local/include',
'-I', RubyInclude(),
'-I', RiceInclude(),
]

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )

def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags

def FlagsForFile( filename ):
  relative_to = DirectoryOfThisScript()
  final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }
