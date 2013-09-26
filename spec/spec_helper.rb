RSpec.configure do |c|
  c.include(Module.new do
    def open_file(path)
      path = File.join(File.expand_path("../", __FILE__), path)
      File.open(path, "rb")
    end
  end)
end
